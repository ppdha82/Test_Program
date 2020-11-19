CONF=./lighttpd.conf.default
HTTPS_PORT=$1
USE_SSL_ENGINE=$2
sed -i "s/\(server.port *= *\).*/\1${HTTPS_PORT}/" ${CONF}
TEST=`grep -n 'server.port' ${CONF} | cut -d: -f1 | head -1`
echo "TEST = "$TEST
TEST=`expr $TEST + 1`
echo "TEST = "$TEST
TEST_END=`expr $TEST + 1`
if [ ${USE_SSL_ENGINE} -eq 1 ]; then
	echo "USE SSL!!!"
	sed -i "${TEST},${TEST}"" s/disable/enable/" ${CONF}
else
	echo "DON'T USE SSL!!!"
	sed -i "${TEST},${TEST}"' s/enable/disable/' ${CONF}
fi

echo "TEST = "$TEST
echo "TEST_END = "$TEST_END
