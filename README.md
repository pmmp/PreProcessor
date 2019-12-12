# PreProcessor
Scripts used to optimise PocketMine-MP before building phars.

These scripts are used by Jenkins to optimize PocketMine-MP source code in production phars.

### PreProcessor.php
This script uses the C preprocessor to pre-process PocketMine-MP source code before it is packaged into a phar. The headers in the `rules/` directory define C macros which are used to preprocess the code and optimize it for use in production.

#### Arguments
- `path`: Path to the PocketMine-MP source code to optimize.