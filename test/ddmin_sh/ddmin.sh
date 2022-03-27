echo "ddmin algorithm test"

rm output/ddmin_output.txt
touch output/ddmin_output.txt

../bin/ddmin ../jsmn/jsondump input/dd.json
