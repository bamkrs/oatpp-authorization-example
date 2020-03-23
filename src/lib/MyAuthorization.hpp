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

#ifndef AUTHORIZATION_EXAMPLE_SRC_LIB_MYAUTHORIZATION_HPP_
#define AUTHORIZATION_EXAMPLE_SRC_LIB_MYAUTHORIZATION_HPP_

#include <oatpp/web/server/handler/AuthorizationHandler.hpp>

/**
 * Implementation of a custom AuthorizationObject to add further fields/methods
 */
class MyAuthorizationObject : public oatpp::web::server::handler::AuthorizationObject {
 public:
  MyAuthorizationObject(v_int64 pId, const oatpp::String& pUser)
  : id(pId), user(pUser)
  {}

  v_int64 id;
  oatpp::String user;
};

/**
 * Implementation of a custom BasicAuthorizationHandler to streamline the authorization process
 * using basic authorization
 */
class MyAuthorization : public oatpp::web::server::handler::BasicAuthorizationHandler {

 public:
  MyAuthorization(const oatpp::String &realm) : BasicAuthorizationHandler(realm) {}

  std::shared_ptr<MyAuthorization> createShared(const oatpp::String &realm) {
    return std::make_shared<MyAuthorization>(realm);
  }

  /**
   * Override the handleAuthorization method to use your own authorization process.
   * Return a nullptr if oatpp should deny the authorization for you.
   * @param userId
   * @param password
   * @return
   */
  std::shared_ptr<AuthorizationObject> authorize(const oatpp::String &userId, const oatpp::String &password) override {

    /**
     * Do your authorization-process here. Call your Database or whatever is needed.
     */
    //ToDo: PLEASE DO NOT HARDCODE YOUR CREDENTIALS!
    if (userId == "root" && password == "hardcodingyourpasswordsisntsafe") {
      return std::make_shared<MyAuthorizationObject>(0, userId);
    } else if (userId == "admin" && password == "thisisrealyjustfordemopurposes") {
      return std::make_shared<MyAuthorizationObject>(1, userId);
    } else if (userId == "user" && password == "pleaselistentous") {
      return std::make_shared<MyAuthorizationObject>(2, userId);
    }
    return nullptr;
  }

};


#endif //AUTHORIZATION_EXAMPLE_SRC_LIB_MYAUTHORIZATION_HPP_
