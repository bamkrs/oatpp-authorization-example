//
//  MyController.hpp
//  web-starter-project
//
//  Created by Leonid on 2/12/18.
//  Copyright © 2018 oatpp. All rights reserved.
//

#ifndef MyController_hpp
#define MyController_hpp

#include "dto/DTOs.hpp"

#include "oatpp/web/server/api/ApiController.hpp"
#include "oatpp/core/macro/codegen.hpp"
#include "oatpp/core/macro/component.hpp"

#include "lib/MyAuthorization.hpp"

/**
 * Sample Api Controller.
 */
class MyController : public oatpp::web::server::api::ApiController {
public:
  /**
   * Constructor with object mapper.
   * @param objectMapper - default object mapper used to serialize/deserialize DTOs.
   */
  MyController(OATPP_COMPONENT(std::shared_ptr<ObjectMapper>, objectMapper))
    : oatpp::web::server::api::ApiController(objectMapper)
  {}
public:
  
/**
 *  Begin ENDPOINTs generation ('ApiController' codegen)
 */
#include OATPP_CODEGEN_BEGIN(ApiController)
  
  ENDPOINT("GET", "/", root) {
    auto dto = MyDto::createShared();
    dto->statusCode = 200;
    dto->message = "Hello World!";
    return createDtoResponse(Status::CODE_200, dto);
  }

  /**
   * Default authorization process, just parse Authorization header and get username/password
   */
  ENDPOINT("GET", "/whoami", whoami, AUTHORIZATION(std::shared_ptr<oatpp::web::server::handler::AuthorizationObject>, authorizationObject)) {
    auto dto = MyDto::createShared();
    dto->statusCode = 200;
    dto->message = "Hello " + authorizationObject->user;
    return createDtoResponse(Status::CODE_200, dto);
  }

  /**
   * Default authorization process, evaluate credentials in endpoint
   */
  ENDPOINT("GET", "/secret", secret, AUTHORIZATION(std::shared_ptr<oatpp::web::server::handler::AuthorizationObject>, authorizationObject)) {
    if(authorizationObject->user == "foo" && authorizationObject->password == "bar") {
      auto dto = MyDto::createShared();
      dto->statusCode = 200;
      dto->message = "Hello " + authorizationObject->user;
      return createDtoResponse(Status::CODE_200, dto);
    }
    auto error = ApiController::handleError(Status::CODE_401, "Unauthorized");
    error->putHeaderIfNotExists(oatpp::web::protocol::http::Header::WWW_AUTHENTICATE, "Basic realm=\"API\"");
    return error;
  }

  // TODO Insert Your endpoints here !!!
  
/**
 *  Finish ENDPOINTs generation ('ApiController' codegen)
 */
#include OATPP_CODEGEN_END(ApiController)
  
};

#endif /* MyController_hpp */
