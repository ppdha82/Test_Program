IP_ADDR=10.0.0.18
RESULT_OUTPUT=pos_test.txt
for i in {1..30}
do
	echo "count = "$i
	sh mfz_test.sh ${IP_ADDR} current_pos >> $RESULT_OUTPUT
	sh mfz_test.sh ${IP_ADDR} zoom_move 80
	sleep 19
	sh mfz_test.sh ${IP_ADDR} current_pos >> $RESULT_OUTPUT
	sh mfz_test.sh ${IP_ADDR} zoom_move 600
	sleep 16
done

sh mfz_test.sh ${IP_ADDR} current_pos >> $RESULT_OUTPUT
