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

#ifndef MyCustomAuthorizationController_hpp
#define MyCustomAuthorizationController_hpp

#include "dto/DTOs.hpp"

#include "oatpp/web/server/api/ApiController.hpp"
#include "oatpp/core/macro/codegen.hpp"
#include "oatpp/core/macro/component.hpp"

#include "lib/MyAuthorization.hpp"

/**
 * Sample Api Controller with custom authorization.
 */
class MyCustomAuthorizationController : public oatpp::web::server::api::ApiController {
 private:
  /**
   * Somehow store a pointer to your Authorization-Handler
   * You can also pass this pointer in your constructor and do not have to instantiate your Autorization-Handler here.
   * Most likely, you want a shared Authorization-Handler for all endpoints.
   */
  std::shared_ptr<MyAuthorization>
      m_auth = std::make_shared<MyAuthorization>("CUSTOMREALM");


 public:
  /**
   * Constructor with object mapper and custom authorization handler.
   * @param objectMapper - default object mapper used to serialize/deserialize DTOs.
   */
  MyCustomAuthorizationController(OATPP_COMPONENT(std::shared_ptr<ObjectMapper>, objectMapper))
      : oatpp::web::server::api::ApiController(objectMapper)
  {

  }
 public:

/**
 *  Begin ENDPOINTs generation ('ApiController' codegen)
 */
#include OATPP_CODEGEN_BEGIN(ApiController)

  /**
   * Custom authorization process, evaluate credentials in custom authorization handler
   */
  ENDPOINT("GET", "/customwhoami", customwhoami, AUTHORIZATION(std::shared_ptr<MyAuthorizationObject>, authorizationObject, m_auth)) {

    auto dto = MyDto::createShared();
    dto->statusCode = 200;
    dto->message = "Hello " + authorizationObject->user;

    OATPP_LOGI("MyCustomAuthorizationController", "/customwhoami called by user '%s' (%d)", authorizationObject->user->c_str(), authorizationObject->id);

    return createDtoResponse(Status::CODE_200, dto);
  }

  // TODO Insert Your endpoints here !!!

/**
 *  Finish ENDPOINTs generation ('ApiController' codegen)
 */
#include OATPP_CODEGEN_END(ApiController)

};

#endif /* MyCustomAuthorizationController_hpp */
