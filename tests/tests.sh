#!/bin/bash

# Curl tests

echo -en "ROOT PAGE\n"
curl localhost:8000
echo ""

echo -en "FULL CORRECT CREATE\n"
curl localhost:8000/create -X POST -H "Content-Type: application/json" \
-d '{"personName":"Egor Moroz","personPhoneNumber":"+1111","personAddress":"Kozlova street 15"}'
echo -en "\n\n"

echo -en "CORRECT PATCH BY ID\n"
curl localhost:8000/update?id=854070473 -X PATCH \
-H "Content-Type: application/json" \
-d '{"personAddress":"Pushkina street 11"}'
echo -en "\n\n"

echo -en "FULL CORRECT CREATE\n"
curl localhost:8000/create -X POST -H "Content-Type: application/json" \
-d '{"personName":"Egor Testov","personPhoneNumber":"+1","personAddress":"GET ALL TEST"}'
echo -en "\n\n"

echo -en "PARTIAL CORRECT CREATE\n"
curl localhost:8000/create -X POST -H "Content-Type: application/json" \
-d '{"personName":"VanekDurachok","personPhoneNumber":"+37544"}'
echo -en "\n\n"

echo -en "PARTIAL CORRECT PATCH BY NAME\n"
curl localhost:8000/update/byname?personName=VanekDurachok -X PATCH \
-H "Content-Type: application/json" \
-d '{"personName":"Vanek Durachok","personAddress":"Pietrusia Brovki street 4"}'
echo -en "\n\n"

echo -en "CORRECT GET CONTACT BY NAME\n"
curl localhost:8000/contact/byname?personName=Vanek%20Durachok
echo -en "\n\n"

echo -en "PARTIAL INCORRECT CREATE\n"
curl localhost:8000/create -X POST -H "Content-Type: application/json" \
-d '{"personFullName":"VanekDurachok","number":"+37544"}'
echo -en "\n\n"

echo -en "PARTIAL INCORRECT CREATE\n"
curl localhost:8000/create -X POST -H "Content-Type: application/json" \
-d '{"personName":"Vanek Durachok","personPhoneNumber":"+37555"}'
echo -en "\n\n"

echo -en "PARTIAL INCORRECT PATCH BY NAME\n"
curl localhost:8000/update/byname?personName=VanekDurachok -X PATCH \
-H "Content-Type: application/json" \
-d '{"personName":"Ivan Durak","address":"Pietrusia Brovki street 4","personPhoneNumber":"+123"}'
echo -en "\n\n"

echo -en "PARTIAL INCORRECT PATCH BY NAME\n"
curl localhost:8000/update/byname?personName=VanekDurachok -X PATCH \
-H "Content-Type: application/json" \
-d '{"personName":"Ivan Durak", "personPhoneNumber":"+123"}'
echo -en "\n\n"

echo -en "PARTIAL CORRECT PATCH BY NAME\n"
curl localhost:8000/update/byname?personName=Vanek%20Durachok -X PATCH \
-H "Content-Type: application/json" \
-d '{"personName":"Ivan Durak"}'
echo -en "\n\n"

echo -en "CORRECT GET CONTACT BY ID\n"
curl localhost:8000/contact?id=854070473
echo -en "\n\n"

echo -en "INCORRECT GET CONTACT BY ID\n"
curl localhost:8000/contact?id=666
echo -en "\n\n"

echo "CORRECT GET CONTACT BY NAME\n"
curl localhost:8000/contact/byname?personName=Egor%20Moroz
echo -en "\n\n"

echo "CORRECT GET CONTACT BY NAME\n"
curl localhost:8000/contact/byname?personName=Ivan%20Durak
echo -en "\n\n"

echo "CORRECT DELETE CONTACT BY ID\n"
curl localhost:8000/delete?id=854070473 -X DELETE
echo -en "\n\n"

echo -en "GET CONTACT BY ID AFTER DELETE. SHOULD FAIL\n"
curl localhost:8000/contact?id=854070473
echo -en "\n\n"

echo -en "CORRECT DELETE CONTACT BY NAME\n"
curl localhost:8000/delete/byname?personName=Ivan%20Durak -X DELETE
echo -en "\n\n"

echo -en "GET CONTACT BY NAME AFTER DELETE. SHOULD FAIL\n"
curl localhost:8000/contact/byname?personName=Ivan%20Durak
echo -en "\n\n"

echo -en "FULL CORRECT CREATE\n"
curl localhost:8000/create -X POST -H "Content-Type: application/json" \
-d '{"personName":"Vanek Pirozhok","personPhoneNumber":"+1111","personAddress":"Kozlova street 15"}'
echo -en "\n\n"

echo -en "CORRECT GET CONTACT ALL\n"
curl localhost:8000/contact/all
echo -en "\n\n"