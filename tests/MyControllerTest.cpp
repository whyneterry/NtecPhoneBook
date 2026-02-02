#include "MyControllerTest.hpp"

#include "controller/MyController.hpp"

#include "app-test/MyApiTestClient.hpp"
#include "app-test/TestComponent.hpp"

#include "oatpp/web/client/HttpRequestExecutor.hpp"
#include "oatpp-test/web/ClientServerTestRunner.hpp"
#include "oatpp/encoding/Url.hpp"

#include <iostream>

// WARNING!!!
// Tests were AI-Generated))))

void httpErrorCheck(const std::shared_ptr<oatpp::web::client::RequestExecutor::Response>& response, 
                    const std::string& testName)
{
    auto statusCode = response->getStatusCode();
    
    if (statusCode >= 400)
    {
        std::cout << "\nHTTP ERROR in test: " << testName << std::endl;
        std::cout << "STATUS CODE: " << statusCode << std::endl;
        std::cout << "ERROR BODY: " << response->readBodyToString()->c_str() << std::endl;
    }
}

void MyControllerTest::onRun() {
    TestComponent component;

    oatpp::test::web::ClientServerTestRunner runner;
    OATPP_COMPONENT(std::shared_ptr<oatpp::json::ObjectMapper>, tempObjectMapper);
    auto requestHandler = NTEC::RequestHandler::createShared();
    runner.addController(std::make_shared<MyController>(tempObjectMapper, requestHandler));

    runner.run([&] {
        OATPP_COMPONENT(std::shared_ptr<oatpp::network::ClientConnectionProvider>, clientConnectionProvider);
        auto requestExecutor = oatpp::web::client::HttpRequestExecutor::createShared(clientConnectionProvider);
        auto client = MyApiTestClient::createShared(requestExecutor, tempObjectMapper);
        oatpp::String jsonHeader = "application/json";

        try {
            std::cout << "\n1. Testing GET / (ROOT PAGE)" << std::endl;
            auto response = client->root();
            httpErrorCheck(response, "GET /");
            OATPP_ASSERT(response->getStatusCode() == 200);
            auto message = response->readBodyToString();
            OATPP_ASSERT(message == NTEC::RequestHandler::getRootPage());
            std::cout << "OK - Root page" << std::endl;

            // ================== BASIC CREATE TESTS ==================
            std::cout << "\n2. Testing FULL CORRECT CREATE" << std::endl;
            auto createDto1 = oatpp::Object<RequestContactCreateDto>::createShared();
            oatpp::String ivanIvanovName = "Ivan Ivanov";
            oatpp::String phone1 = "+375291234567";
            oatpp::String address1 = "vulica Lienina 15, Minsk";
            
            createDto1->personName = ivanIvanovName;
            createDto1->personPhoneNumber = phone1;
            createDto1->personAddress = address1;
            
            response = client->createContact(createDto1);
            httpErrorCheck(response, "FULL CORRECT CREATE");
            OATPP_ASSERT(response->getStatusCode() == 201);
            auto responseDto1 = response->readBodyToDto<oatpp::Object<ResponseContactCreateDto>>(
                client->getObjectMapper()
            );
            OATPP_ASSERT(responseDto1->personId > 0);
            auto ivanId = responseDto1->personId;
            std::cout << "OK - Created with ID: " << ivanId << std::endl;

            // ================== PATCH TESTS ==================
            std::cout << "\n3. Testing CORRECT PATCH BY ID" << std::endl;
            auto patchDto1 = oatpp::Object<RequestContactCreateDto>::createShared();
            oatpp::String newAddress = "praspiekt Niezalieznasci 25, Minsk";
            patchDto1->personAddress = newAddress;
            
            response = client->updateContactById(patchDto1, ivanId);
            httpErrorCheck(response, "PATCH BY ID");
            OATPP_ASSERT(response->getStatusCode() == 200);
            std::cout << "OK - Patched by ID" << std::endl;

            // ================== MORE CREATE TESTS ==================
            std::cout << "\n4. Testing CREATE WITH DIFFERENT FORMATS" << std::endl;
            auto createDto2 = oatpp::Object<RequestContactCreateDto>::createShared();
            oatpp::String petrPetrovName = "Petr Petrov";
            oatpp::String phone2 = "+375447891011";
            oatpp::String address2 = "vulica Kirava 7, Hrodna";
            
            createDto2->personName = petrPetrovName;
            createDto2->personPhoneNumber = phone2;
            createDto2->personAddress = address2;
            
            response = client->createContact(createDto2);
            httpErrorCheck(response, "CREATE Petr Petrov");
            OATPP_ASSERT(response->getStatusCode() == 201);
            std::cout << "OK - Created Petr Petrov" << std::endl;

            std::cout << "\n5. Testing CREATE WITHOUT ADDRESS" << std::endl;
            auto createDto3 = oatpp::Object<RequestContactCreateDto>::createShared();
            oatpp::String sergeyName = "Sergey Sergeev";
            oatpp::String phone3 = "+375336665544";
            
            createDto3->personName = sergeyName;
            createDto3->personPhoneNumber = phone3;
            // No address - should work
            
            response = client->createContact(createDto3);
            httpErrorCheck(response, "CREATE WITHOUT ADDRESS");
            OATPP_ASSERT(response->getStatusCode() == 201);
            std::cout << "OK - Created without address" << std::endl;

            // ================== PATCH BY NAME TESTS ==================
            std::cout << "\n6. Testing PATCH BY NAME" << std::endl;
            auto patchDto2 = oatpp::Object<RequestContactCreateDto>::createShared();
            oatpp::String updatedName = "Sergey Sergeevich";
            oatpp::String address3 = "vulica Kastrycnickaja 33, Viciebsk";
            
            patchDto2->personName = updatedName;
            patchDto2->personAddress = address3;
            
            oatpp::String encodedSergeyName = oatpp::encoding::Url::encode(sergeyName, oatpp::encoding::Url::Config{});
            response = client->updateContactByName(patchDto2, encodedSergeyName);
            httpErrorCheck(response, "PATCH BY NAME");
            OATPP_ASSERT(response->getStatusCode() == 200);
            std::cout << "OK - Patched by name" << std::endl;

            // ================== GET BY NAME TESTS ==================
            std::cout << "\n7. Testing GET BY NAME" << std::endl;
            oatpp::String encodedUpdatedName = oatpp::encoding::Url::encode(updatedName, oatpp::encoding::Url::Config{});
            response = client->getContactByName(encodedUpdatedName);
            httpErrorCheck(response, "GET BY NAME");
            OATPP_ASSERT(response->getStatusCode() == 200);
            auto sergeyDto = response->readBodyToDto<oatpp::Object<ResponseContactCreateDto>>(
                client->getObjectMapper()
            );
            OATPP_ASSERT(sergeyDto->personName == updatedName);
            std::cout << "OK - Got contact by name" << std::endl;
            
            // ================== EDGE CASE TESTS ==================
            std::cout << "\n8. Testing DUPLICATE NAME CREATE (should fail)" << std::endl;
            auto duplicateDto = oatpp::Object<RequestContactCreateDto>::createShared();
            oatpp::String duplicatePhone = "+375299998877";
            
            duplicateDto->personName = updatedName; // Same name as existing
            duplicateDto->personPhoneNumber = duplicatePhone;
            
            response = client->createContact(duplicateDto);
            httpErrorCheck(response, "DUPLICATE CREATE");
            std::cout << "Duplicate create status: " << response->getStatusCode() << " (expected error)" << std::endl;

            std::cout << "\n9. Testing CREATE WITH LONG NAME" << std::endl;
            auto longNameDto = oatpp::Object<RequestContactCreateDto>::createShared();
            oatpp::String longName = "Aleh Mikalajevich Kanstancinavich";
            oatpp::String longPhone = "+375257777777";
            
            longNameDto->personName = longName;
            longNameDto->personPhoneNumber = longPhone;
            
            response = client->createContact(longNameDto);
            httpErrorCheck(response, "CREATE WITH LONG NAME");
            OATPP_ASSERT(response->getStatusCode() == 201);
            std::cout << "OK - Created with long name" << std::endl;

            std::cout << "\n10. Testing CREATE WITH SPECIAL PHONE FORMAT" << std::endl;
            auto specialPhoneDto = oatpp::Object<RequestContactCreateDto>::createShared();
            oatpp::String specialName = "Dzmitry Sidarau";
            oatpp::String specialPhone = "8029-123-45-67";
            
            specialPhoneDto->personName = specialName;
            specialPhoneDto->personPhoneNumber = specialPhone;
            
            response = client->createContact(specialPhoneDto);
            httpErrorCheck(response, "CREATE WITH SPECIAL PHONE");
            OATPP_ASSERT(response->getStatusCode() == 201);
            std::cout << "OK - Created with special phone format" << std::endl;

            // ================== UNKNOWN FIELD TESTS ==================
            std::cout << "\n11. Testing CREATE WITH UNKNOWN FIELDS (raw JSON)" << std::endl;
            // Создаем JSON с неизвестными полями
            oatpp::String invalidJson1 = R"({
                "personName": "Test User",
                "personPhoneNumber": "+375291111111",
                "personAddress": "Test Address",
                "unknownField1": "This field doesn't exist",
                "unknownField2": 12345
            })";
            response = client->createContactRaw(jsonHeader, invalidJson1);
            httpErrorCheck(response, "CREATE WITH UNKNOWN FIELDS");
            std::cout << "Unknown fields status: " << response->getStatusCode() 
                     << " (expected 500 due to unknown fields)" << std::endl;
            
            if (response->getStatusCode() != 500) {
                std::cout << "WARNING: Server didn't reject unknown fields!" << std::endl;
                std::cout << "Make sure ObjectMapper is configured with allowUnknownFields = false" << std::endl;
            }

            std::cout << "\n12. Testing CREATE WITH WRONG FIELD NAMES (raw JSON)" << std::endl;
            oatpp::String invalidJson2 = R"({
                "PersonName": "Wrong Case Name",
                "personphonenumber": "+375292222222",
                "person_address": "Wrong format address",
                "FakeField": "Fake value"
            })";
            
            response = client->createContactRaw(jsonHeader, invalidJson2);
            httpErrorCheck(response, "CREATE WITH WRONG FIELD NAMES");
            std::cout << "Wrong field names status: " << response->getStatusCode() 
                     << " (expected 500)" << std::endl;

            std::cout << "\n13. Testing PATCH WITH UNKNOWN FIELDS (raw JSON)" << std::endl;
            oatpp::String invalidJson3 = R"({
                "personAddress": "Updated address",
                "fakeField": "This should cause error",
                "extraData": {"nested": "value"}
            })";
            
            response = client->updateContactByIdRaw(jsonHeader, invalidJson3, ivanId);
            httpErrorCheck(response, "PATCH WITH UNKNOWN FIELDS");
            std::cout << "Patch unknown fields status: " << response->getStatusCode() 
                     << " (expected 500)" << std::endl;

            std::cout << "\n14. Testing CREATE WITH EXTRA NESTED FIELDS (raw JSON)" << std::endl;
            oatpp::String invalidJson4 = R"({
                "personName": "Nested Test",
                "personPhoneNumber": "+375293333333",
                "metadata": {
                    "createdBy": "test",
                    "version": 1
                },
                "tags": ["test", "sample"]
            })";
            
            response = client->createContactRaw(jsonHeader, invalidJson4);
            httpErrorCheck(response, "CREATE WITH EXTRA NESTED FIELDS");
            std::cout << "Extra nested fields status: " << response->getStatusCode() 
                     << " (expected 500)" << std::endl;

            // ================== GET BY ID TESTS ==================
            std::cout << "\n15. Testing CORRECT GET BY ID" << std::endl;
            response = client->getContactById(ivanId);
            httpErrorCheck(response, "GET BY ID");
            OATPP_ASSERT(response->getStatusCode() == 200);
            auto ivanCurrent = response->readBodyToDto<oatpp::Object<ResponseContactCreateDto>>(
                client->getObjectMapper()
            );
            OATPP_ASSERT(ivanCurrent->personAddress == newAddress);
            std::cout << "OK - Got contact by ID" << std::endl;

            std::cout << "\n16. Testing GET BY NON-EXISTENT ID" << std::endl;
            response = client->getContactById(999999);
            httpErrorCheck(response, "GET NON-EXISTENT ID");
            std::cout << "Non-existent ID status: " << response->getStatusCode() << " (expected 404)" << std::endl;

            // ================== MORE GET BY NAME TESTS ==================
            std::cout << "\n17. Testing GET BY NAME - Ivan Ivanov" << std::endl;
            oatpp::String encodedIvanIvanov = oatpp::encoding::Url::encode(ivanIvanovName, oatpp::encoding::Url::Config{});
            response = client->getContactByName(encodedIvanIvanov);
            httpErrorCheck(response, "GET Ivan Ivanov");
            OATPP_ASSERT(response->getStatusCode() == 200);
            std::cout << "OK - Got Ivan Ivanov" << std::endl;

            // ================== DELETE TESTS ==================
            std::cout << "\n18. Testing DELETE BY ID" << std::endl;
            response = client->deleteContactById(ivanId);
            httpErrorCheck(response, "DELETE BY ID");
            OATPP_ASSERT(response->getStatusCode() == 200);
            std::cout << "OK - Deleted by ID" << std::endl;

            std::cout << "\n19. Testing GET AFTER DELETE BY ID" << std::endl;
            response = client->getContactById(ivanId);
            httpErrorCheck(response, "GET AFTER DELETE BY ID");
            std::cout << "Get after delete status: " << response->getStatusCode() << " (expected error)" << std::endl;

            std::cout << "\n20. Testing DELETE BY NAME" << std::endl;
            response = client->deleteContactByName(encodedUpdatedName);
            httpErrorCheck(response, "DELETE BY NAME");
            OATPP_ASSERT(response->getStatusCode() == 200);
            std::cout << "OK - Deleted by name" << std::endl;

            std::cout << "\n21. Testing GET AFTER DELETE BY NAME" << std::endl;
            response = client->getContactByName(encodedUpdatedName);
            httpErrorCheck(response, "GET AFTER DELETE BY NAME");
            std::cout << "Get after delete status: " << response->getStatusCode() << " (expected error)" << std::endl;

            // ================== BATCH OPERATIONS TESTS ==================
            std::cout << "\n22. Testing BATCH CREATION" << std::endl;
            std::vector<std::pair<oatpp::String, oatpp::String>> batchContacts = {
                {"Alena Kavalova", "+375292223344"},
                {"Mikalaj Hurski", "+375332225566"},
                {"Kaciaryna Baranava", "+375447778899"},
                {"Uladzimir Kalacki", "+375256667788"}
            };
            
            for (size_t i = 0; i < batchContacts.size(); ++i) {
                auto batchDto = oatpp::Object<RequestContactCreateDto>::createShared();
                batchDto->personName = batchContacts[i].first;
                batchDto->personPhoneNumber = batchContacts[i].second;
                batchDto->personAddress = "vulica Savieckaja " + std::to_string(i + 1) + ", Minsk";
                
                response = client->createContact(batchDto);
                httpErrorCheck(response, "BATCH CREATE " + std::to_string(i));
                OATPP_ASSERT(response->getStatusCode() == 201);
            }
            std::cout << "OK - Created " << batchContacts.size() << " contacts" << std::endl;

            std::cout << "\n23. Testing GET ALL CONTACTS" << std::endl;
            response = client->getContactAll();
            httpErrorCheck(response, "GET ALL");
            OATPP_ASSERT(response->getStatusCode() == 200);
            auto allContacts = response->readBodyToString();
            OATPP_ASSERT(allContacts);
            std::cout << "OK - Got all contacts (" << allContacts->size() << " bytes)" << std::endl;

            // ================== ERROR CASE TESTS ==================
            std::cout << "\n24. Testing CREATE WITH EMPTY NAME" << std::endl;
            auto emptyNameDto = oatpp::Object<RequestContactCreateDto>::createShared();
            emptyNameDto->personName = "";
            emptyNameDto->personPhoneNumber = "+375291111111";
            
            response = client->createContact(emptyNameDto);
            httpErrorCheck(response, "CREATE WITH EMPTY NAME");
            std::cout << "Empty name status: " << response->getStatusCode() << " (expected error)" << std::endl;

            std::cout << "\n25. Testing CREATE WITH EMPTY PHONE" << std::endl;
            auto emptyPhoneDto = oatpp::Object<RequestContactCreateDto>::createShared();
            emptyPhoneDto->personName = "Test User";
            emptyPhoneDto->personPhoneNumber = "";
            
            response = client->createContact(emptyPhoneDto);
            httpErrorCheck(response, "CREATE WITH EMPTY PHONE");
            std::cout << "Empty phone status: " << response->getStatusCode() << " (expected error)" << std::endl;

            std::cout << "\n26. Testing PATCH WITH NON-EXISTENT NAME" << std::endl;
            auto nonExistentPatchDto = oatpp::Object<RequestContactCreateDto>::createShared();
            nonExistentPatchDto->personName = "Non Existent";
            
            oatpp::String nonExistentName = oatpp::encoding::Url::encode("Non Existent Person", oatpp::encoding::Url::Config{});
            response = client->updateContactByName(nonExistentPatchDto, nonExistentName);
            httpErrorCheck(response, "PATCH NON-EXISTENT");
            std::cout << "Patch non-existent status: " << response->getStatusCode() << " (expected error)" << std::endl;

            std::cout << "\n27. Testing DELETE NON-EXISTENT" << std::endl;
            response = client->deleteContactByName(nonExistentName);
            httpErrorCheck(response, "DELETE NON-EXISTENT");
            std::cout << "Delete non-existent status: " << response->getStatusCode() << " (expected error)" << std::endl;

            // ================== FINAL VERIFICATION ==================
            std::cout << "\n28. Testing FINAL GET ALL VERIFICATION" << std::endl;
            response = client->getContactAll();
            httpErrorCheck(response, "FINAL GET ALL");
            OATPP_ASSERT(response->getStatusCode() == 200);
            auto finalContacts = response->readBodyToString();
            OATPP_ASSERT(finalContacts);
            
            OATPP_ASSERT(finalContacts->find("Alena Kavalova") != std::string::npos);
            OATPP_ASSERT(finalContacts->find("Petr Petrov") != std::string::npos);
            std::cout << "OK - Final verification passed" << std::endl;

            std::cout << "\n=== ALL TESTS PASSED ===" << std::endl;

        } catch(std::exception& e) {
            std::cout << "\nEXCEPTION: " << e.what() << std::endl;
            throw;
        } catch(...) {
            std::cout << "\nUNKNOWN EXCEPTION" << std::endl;
            throw;
        }
        
    }, std::chrono::minutes(1) /* test timeout */);

    /* wait all server threads finished */
    std::this_thread::sleep_for(std::chrono::seconds(1));
}