
#define Binary::readBool(data) (data !== "\x00")
#define Binary::writeBool(data) (data ? "\x01" : "\x00")

#define Binary::readByte(data) (ord(data))
#define Binary::readSignedByte(data) (ord(data) << 56 >> 56)
#define Binary::writeByte(data) (chr(data))

#define Binary::readShort(data) (unpack("n", data)[1])
#define Binary::readSignedShort(data) (unpack("n", data)[1] << 48 >> 48)
#define Binary::readLShort(data) (unpack("v", data)[1])
#define Binary::readSignedLShort(data) (unpack("v", data)[1] << 48 >> 48)
#define Binary::writeShort(data) (pack("n", data))
#define Binary::writeLShort(data) (pack("v", data))

#define Binary::readTriad(data) unpack("N", "\x00" . data)[1]
#define Binary::readLTriad(data) unpack("V", data . "\x00")[1]
#define Binary::writeTriad(data) (substr(pack("N", data), 1))
#define Binary::writeLTriad(data) (substr(pack("V", data), 0, -1))

#define Binary::readInt(data) (unpack("N", data)[1] << 32 >> 32)
#define Binary::readLInt(data) (unpack("V", data)[1] << 32 >> 32)
#define Binary::writeInt(data) (pack("N", data))
#define Binary::writeLInt(data) (pack("V", data))

#define Binary::writeLong(data) (pack("NN", data >> 32, data & 0xFFFFFFFF))
#define Binary::writeLLong(data) (pack("VV", data >> 32, data & 0xFFFFFFFF))

#define Binary::readFloat(data) (ENDIANNESS === 0 ? unpack("f", data)[1] : unpack("f", strrev(data))[1])
#define Binary::readRoundedFloat(data, accuracy) (round(Binary::readFloat(data), accuracy))
#define Binary::readLFloat(data) (ENDIANNESS === 0 ? unpack("f", strrev(data))[1] : unpack("f", data)[1])
#define Binary::readRoundedLFloat(data, accuracy) (round(Binary::readLFloat(data), accuracy))
#define Binary::writeFloat(data) (ENDIANNESS === 0 ? pack("f", data) : strrev(pack("f", data)))
#define Binary::writeLFloat(data) (ENDIANNESS === 0 ? strrev(pack("f", data)) : pack("f", data))

#define Binary::readDouble(data) (ENDIANNESS === 0 ? unpack("d", data)[1] : unpack("d", strrev(data))[1])
#define Binary::readLDouble(data) (ENDIANNESS === 0 ? unpack("d", strrev(data))[1] : unpack("d", data)[1])
#define Binary::writeDouble(data) (ENDIANNESS === 0 ? pack("d", data) : strrev(pack("d", data)))
#define Binary::writeLDouble(data) (ENDIANNESS === 0 ? strrev(pack("d", data)) : pack("d", data))
