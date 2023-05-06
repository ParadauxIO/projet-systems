#!/bin/bash
if ! result=$(bc <<< "$1"); then
  echo "Invalid sum"
  exit
fi

if [ "$result" -gt 99 ]; then
    # If the result is greater than 99, add the result to what the cow is saying
    cowsay "Expression: $1 Result: $result"
else
      cowsay -e " $result" "$1"
fi