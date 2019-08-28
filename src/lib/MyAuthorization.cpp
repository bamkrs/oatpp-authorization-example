/**
 * @file MyAuthorization.cpp
 * @author Benedikt-Alexander Mokroß <bam@icognize.de>
 * @date 2019-08-28
 * @brief
 *
 * Copyright (c) 2019 iCOGNIZE GmbH. All rights reserved.
 */

#include "MyAuthorization.hpp"

std::shared_ptr<oatpp::web::server::handler::AuthorizationObject> MyAuthorization::handleAuthorization(const oatpp::String &header) {

  /**
   * You can either parse the header yourself or - in case of basic auth - use the default authorizationObject to do this for you
   */
  auto defaultAuthorization = oatpp::web::server::handler::DefaultAuthorizationHandler::defaultAuthorizationObject(header);

  auto myAuthorization = std::make_shared<MyAuthorizationObject>();
  myAuthorization->user = defaultAuthorization->user;
  myAuthorization->password = defaultAuthorization->password;

  /**
   * Now implement your own authorization process, e.g. a database-query
   * We just hardcode some examples.
   */
  if(myAuthorization->user == "foo" && myAuthorization->password == "bar") {

    myAuthorization->email = "foobar@oatpp.io";
    myAuthorization->id = 1337;

  } else if(myAuthorization->user == "john" && myAuthorization->password == "doe") {

    myAuthorization->email = "johndoe@oatpp.io";
    myAuthorization->id = 0;

  } else {

    /**
     * You can return nullptr if you want oatpp to deny the request e.g. in case of a failed authorization
     * Or return an AuthorizationObject and evaluate a successfull authorization in your endpoint, its up to you!
     */
    return nullptr;

  }

  /**
   * Return your authorization object. oatpp takes care to cast it back to your in AUTHORIZATION(std::shared_ptr<TYPE>, NAME) specified type
   */
  return myAuthorization;
}

bool MyAuthorizationObject::isAdmin() {
  return id == oatpp::Int64(0);
}
