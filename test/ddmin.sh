echo "ddmin algorithm test"

rm output/ddmin_output.txt
touch output/ddmin_output.txt

../bin/ddmin input/jsondump input/ddmin_input.json output/ddmin_output.txt

cat output/ddmin_output.txt