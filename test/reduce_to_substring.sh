echo "reduce_to_substring split test case "

output=`../bin/substring ../bin/jsondump input/split_case.json`
answer="input/split_case1.json"

if [ "$answer" = "$output" ] ; then
    echo "correct answer"
else
    echo "wrong answer"
fi

echo "reduce_to_substring not split test case"

output=`../bin/substring ../bin/jsondump input/not_split_case.json`
answer="input/not_split_case.json"

if [ "$answer" = "$output" ] ; then
    echo "correct answer"
else
    echo "wrong answer"
fi