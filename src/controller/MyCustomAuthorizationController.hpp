/**
 * @file MyCustomAuthorizationController.cpp
 * @author Benedikt-Alexander Mokroß <bam@icognize.de>
 * @date 2019-08-28
 * @brief <ToDo>
 *
 * Copyright (c) 2019 iCOGNIZE GmbH. All rights reserved.
 */

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
 public:
  /**
   * Constructor with object mapper and custom authorization handler.
   * @param objectMapper - default object mapper used to serialize/deserialize DTOs.
   */
  MyCustomAuthorizationController(OATPP_COMPONENT(std::shared_ptr<ObjectMapper>, objectMapper))
      : oatpp::web::server::api::ApiController(objectMapper)
  {
    /**
     * Register a custom authorization handler, setAuthorizationHandler is public
     */
    setAuthorizationHandler(std::make_shared<MyAuthorization>());
  }
 public:

/**
 *  Begin ENDPOINTs generation ('ApiController' codegen)
 */
#include OATPP_CODEGEN_BEGIN(ApiController)

  /**
   * Custom authorization process, evaluate credentials in custom authorization handler
   */
  ENDPOINT("GET", "/moresecret", moresecret, AUTHORIZATION(std::shared_ptr<MyAuthorizationObject>, authorizationObject)) {

    auto dto = MyDto::createShared();
    dto->statusCode = 200;
    dto->message = "Hello " + authorizationObject->user;

    // sendMailTo(dto->email, "New Login", "We detected a new login [...]");

    if(authorizationObject->isAdmin()) {
      dto->message = dto->message + " - Watch out! We got an admin over here!";
    }

    return createDtoResponse(Status::CODE_200, dto);

  }

  // TODO Insert Your endpoints here !!!

/**
 *  Finish ENDPOINTs generation ('ApiController' codegen)
 */
#include OATPP_CODEGEN_END(ApiController)

};

#endif /* MyCustomAuthorizationController_hpp */
