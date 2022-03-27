echo "reduce_to_substring split test case "

output=`../bin/substring input/jsondump input/substring_split_case.json 2`
answer="input/substring_split_case1.json"

if [ "$answer" = "$output" ] ; then
    echo "correct answer"
else
    echo "wrong answer"
fi

echo "reduce_to_substring not split test case"

output=`../bin/substring input/jsondump input/substring_not_split_case.json 2`
answer="input/substring_not_split_case.json"

if [ "$answer" = "$output" ] ; then
    echo "correct answer"
else
    echo "wrong answer"
fi