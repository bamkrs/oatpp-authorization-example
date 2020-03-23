/***************************************************************************
 *
 * Project         _____    __   ____   _      _
 *                (  _  )  /__\ (_  _)_| |_  _| |_
 *                 )(_)(  /(__)\  )( (_   _)(_   _)
 *                (_____)(__)(__)(__)  |_|    |_|
 *
 *
 * Copyright 2018-present, Leonid Stryzhevskyi <lganzzzo@gmail.com>
 *                         Benedikt-Alexander Mokroß <oatpp@bamkrs.de>
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 ***************************************************************************/

#include "MyControllerTest.hpp"

#include "controller/MyController.hpp"
#include "controller/MyCustomAuthorizationController.hpp"

#include "app/MyApiTestClient.hpp"
#include "app/TestComponent.hpp"

#include "oatpp/web/client/HttpRequestExecutor.hpp"

#include "oatpp-test/web/ClientServerTestRunner.hpp"

void MyControllerTest::onRun() {

  /* Register test components */
  TestComponent component;

  /* Create client-server test runner */
  oatpp::test::web::ClientServerTestRunner runner;

  /* Add MyController endpoints to the router of the test server */
  runner.addController(std::make_shared<MyController>());
  runner.addController(std::make_shared<MyCustomAuthorizationController>());

  /* Run test */
  runner.run([this, &runner] {

    /* Get client connection provider for Api Client */
    OATPP_COMPONENT(std::shared_ptr<oatpp::network::ClientConnectionProvider>, clientConnectionProvider);

    /* Get object mapper component */
    OATPP_COMPONENT(std::shared_ptr<oatpp::data::mapping::ObjectMapper>, objectMapper);

    /* Create http request executor for Api Client */
    auto requestExecutor = oatpp::web::client::HttpRequestExecutor::createShared(clientConnectionProvider);

    /* Create Test API client */
    auto client = MyApiTestClient::createShared(requestExecutor, objectMapper);

    {
      /* Call server API */
      /* Call root endpoint of MyController */
      auto getRootResponse = client->getRoot();

      /* Assert that server responds with 200 */
      OATPP_ASSERT(getRootResponse->getStatusCode() == 200);

      /* Read response body as MessageDto */
      auto getRootMessage = getRootResponse->readBodyToDto<MyDto>(objectMapper.get());

      /* Assert that received message is as expected */
      OATPP_ASSERT(getRootMessage);
      OATPP_ASSERT(getRootMessage->statusCode->getValue() == 200);
      OATPP_ASSERT(getRootMessage->message == "Hello World!");
    }

    {
      auto whoamiResponse = client->whoami("john:doe");
      OATPP_ASSERT(whoamiResponse->getStatusCode() == 200);

      auto whoamiMessage = whoamiResponse->readBodyToDto<MyDto>(objectMapper.get());
      OATPP_ASSERT(whoamiMessage);
      OATPP_ASSERT(whoamiMessage->message == "Hello john");
    }

    {
      auto secretResponse = client->secret("foo:bar");
      OATPP_ASSERT(secretResponse->getStatusCode() == 200);

      auto secretMessage = secretResponse->readBodyToDto<MyDto>(objectMapper.get());
      OATPP_ASSERT(secretMessage);
      OATPP_ASSERT(secretMessage->message == "Hello foo");
    }

    {
      auto invalidSecretResponse = client->secret("john:doe");
      OATPP_ASSERT(invalidSecretResponse->getStatusCode() == 401);
    }

    {
      auto moreSecretResponse = client->moreSecret("john:doe");
      OATPP_ASSERT(moreSecretResponse->getStatusCode() == 200);

      auto moreSecretMessage = moreSecretResponse->readBodyToDto<MyDto>(objectMapper.get());
      OATPP_ASSERT(moreSecretMessage);
      OATPP_ASSERT(moreSecretMessage->message == "Hello john - Watch out! We got an admin over here!");
    }

    {
      auto invalidMoreSecretResponse = client->moreSecret("alice:bob");
      OATPP_ASSERT(invalidMoreSecretResponse->getStatusCode() == 401);
    }

  }, std::chrono::minutes(10) /* test timeout */);

  /* wait all server threads finished */
  std::this_thread::sleep_for(std::chrono::seconds(1));

}
