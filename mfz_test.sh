echo ""
if [[ $2 == "zoom_in" ]]; then
echo "RUN "$2
curl http://$1/cgi-bin/setup_ajax_sys_2motor.cgi -d category=2motor_control -d parameter1=$2 -d parameter2=down
sleep $3
curl http://$1/cgi-bin/setup_ajax_sys_2motor.cgi -d category=2motor_control -d parameter1=$2 -d parameter2=up
fi

if [[ $2 == "zoom_out" ]]; then
echo "RUN "$2
curl http://$1/cgi-bin/setup_ajax_sys_2motor.cgi -d category=2motor_control -d parameter1=$2 -d parameter2=down
sleep $3
curl http://$1/cgi-bin/setup_ajax_sys_2motor.cgi -d category=2motor_control -d parameter1=$2 -d parameter2=up
fi

if [[ $2 == "base" ]]; then
echo "RUN "$2
curl http://$1/cgi-bin/setup_ajax_sys_2motor.cgi -d category=2motor_control -d parameter1=$2
fi

if [[ $2 == "current_pos" ]]; then
echo "RUN "$2
curl http://$1/cgi-bin/setup_ajax_sys_2motor.cgi -d category=2motor_control -d parameter1=$2
fi


if [[ $2 == "zoom_move" ]]; then
echo "RUN "$2
curl http://$1/cgi-bin/setup_ajax_sys_2motor.cgi -d category=2motor_control -d parameter1=$2 -d parameter2=$3
fi


if [[ $2 == "AF_smart" ]]; then
echo "RUN "$2
curl http://$1/cgi-bin/setup_ajax_sys_2motor.cgi -d category=2motor_control -d parameter1=$2
fi

if [[ $2 == "gen_tbl" ]]; then
echo "RUN "$2
curl http://$1/cgi-bin/setup_ajax_sys_2motor.cgi -d category=2motor_control -d parameter1=$2
fi

echo ""
