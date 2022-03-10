echo "split function test case"

answer0=`cat ./output/split_answer0.json`
answer1=`cat ./output/split_answer1.json`
../bin/split ./input/ddmin_input.json 2

output0=`cat ./input/ddmin_input0.json`
output1=`cat ./input/ddmin_input1.json`

if [ "$answer0" = "$output0" ]; then
    if [ "$answer1" = "$output1" ]; then
        echo "correct answer"
    else
        echo "wrong answer"
    fi
else   
    echo "wrong answer"
fi