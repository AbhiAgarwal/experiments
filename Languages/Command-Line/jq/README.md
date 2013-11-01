jq - sed for JSON
======

Use case:

`curl -s 'http://api.giphy.com/v1/gifs/recent?api_key=dc6zaTOxFJmzC' > file.json`
`< file.json -c '.data[]'` (gets everything inside the section "data")
`< file.json jq -c '.data[] | {type}'` (gets all the types inside each "data")

