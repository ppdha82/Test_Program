IN_FILE=$1
OUT_FILE=$2
ENC_KEY=$3

ENC_KEY_HASH=`echo -n "${ENC_KEY}" | sha256sum | cut -f 1 -d ' '`
echo "ENC_KEY_HASH="$ENC_KEY_HASH

echo "encrypting"
openssl aes-256-cbc -salt -in $IN_FILE -out $OUT_FILE -pass pass:$ENC_KEY_HASH

echo "decrypting"
openssl aes-256-cbc -d -in $OUT_FILE -out $IN_FILE.dec -pass pass:$ENC_KEY_HASH
