echo "split function test case"

# answer0=`cat ./output/split_answer0.json`
# answer1=`cat ./output/split_answer1.json`
../bin/split ./input/split_input.txt 4

cat input/split_input0.txt
echo ""
cat input/split_input1.txt
echo ""
cat input/split_input2.txt
echo ""
cat input/split_input3.txt
# output0=`cat ./input/ddmin_input_manually0.json`
# output1=`cat ./input/ddmin_input_manually1.json`

# if [ "$answer0" = "$output0" ]; then
#     if [ "$answer1" = "$output1" ]; then
#         echo "correct answer"
#     else
#         echo "wrong answer"
#     fi
# else   
#     echo "wrong answer"
# fi