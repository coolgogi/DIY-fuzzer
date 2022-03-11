echo "ddmin algorithm test"

rm output/ddmin_output.txt
touch output/ddmin_output.txt

../bin/ddmin ../jsmn/jsondump input/dd-3-5-9-2-3-4-8-7-10-16.json
