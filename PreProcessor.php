<?php

define("THIS_PATH", realpath(dirname(__FILE__)));

$opts = getopt("", ["path:"]);

if(!isset($opts["path"])){
	echo "Provide a path to process using --path" . PHP_EOL;
	exit(1);
}

$path = realpath($opts["path"]);
if($path === false){
	fwrite(STDERR, "Path " . $opts["path"] . " does not exist or permission denied" . PHP_EOL);
	exit(1);
}

function process($code, array $extraDefine = []){
	$descriptor = [
		0 => ["pipe", "r"],
		1 => ["pipe", "w"],
		2 => ["pipe", "pipe", "a"]
	];

	$extra = "";

	foreach($extraDefine as $k => $v){
		$extra .= "-D $k=$v ";
	}

	$process = proc_open("cpp -traditional-cpp -nostdinc -include '" . THIS_PATH . "/processed/rules/PocketMine.h' -I '" . THIS_PATH . "/processed' " . $extra . " -E -C -P -D FULL - -o -", $descriptor, $pipes);
	fwrite($pipes[0], $code);
	fclose($pipes[0]);
	$out = stream_get_contents($pipes[1]);
	fclose($pipes[1]);
	$error = @stream_get_contents($pipes[2]);
	if(trim($error) != ""){
		throw new \RuntimeException("Failed to preprocess code: $error");
	}
	fclose($pipes[2]);
	proc_close($process);
	if($out === "" or $out === false){
		throw new \RuntimeException("Preprocessor returned empty output");
	}

	return substr($out, strpos($out, "<?php"));
}

@mkdir(THIS_PATH . "/processed/rules/", 0777, true);

foreach(glob(THIS_PATH . "/rules/*.h") as $file){
	if(substr($file, -2) !== ".h"){
		continue;
	}

	$lines = file($file);
	foreach($lines as $n => &$line){
		if(trim($line) === ""){
			//Get rid of extra newlines
			$line = "";
			continue;
		}

		$line = str_replace(["::", "->", '$'], ["__STATIC_CALL__", "__METHOD_CALL__", "__VARIABLE_DOLLAR__"], $line);
	}

	file_put_contents(THIS_PATH . "/processed/rules/" . substr($file, strrpos($file, "/")), implode("", $lines));
}

foreach(new RecursiveIteratorIterator(new RecursiveDirectoryIterator($path)) as $path => $f){
	if(substr($path, -4) !== ".php"){
		continue;
	}
	$oldCode = file_get_contents($path);
	$code = str_replace(["__STATIC_CALL__", "__METHOD_CALL__", "__VARIABLE_DOLLAR__", "__STARTING_COMMENT_BADLINE__"], ["::", "->", '$', " * |  _ \\ ___   ___| | _____| |_|  \\/  (_)_ __   ___      |  \\/  |  _ \\"],
		process(str_replace(["::", "->", '$', " * |  _ \\ ___   ___| | _____| |_|  \\/  (_)_ __   ___      |  \\/  |  _ \\"], ["__STATIC_CALL__", "__METHOD_CALL__", "__VARIABLE_DOLLAR__", "__STARTING_COMMENT_BADLINE__"], $oldCode))
	);
	if(trim($oldCode) !== trim($code)){
		echo "Processed $path\n";
		file_put_contents($path, $code);
		exec(PHP_BINARY . ' -l ' . $path, $output, $exitCode);
		if($exitCode !== 0){
			fwrite(STDERR, "Preprocessor broke file $path\n");
			fwrite(STDERR, implode("\n", $output));
			exit(1);
		}
	}
}
