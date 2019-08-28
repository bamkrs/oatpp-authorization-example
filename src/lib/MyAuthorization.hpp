/**
 * @file MyAuthorization.hpp
 * @author Benedikt-Alexander Mokroß <bam@icognize.de>
 * @date 2019-08-28
 * @brief
 *
 * Copyright (c) 2019 iCOGNIZE GmbH. All rights reserved.
 */

#ifndef AUTHORIZATION_EXAMPLE_SRC_LIB_MYAUTHORIZATION_HPP_
#define AUTHORIZATION_EXAMPLE_SRC_LIB_MYAUTHORIZATION_HPP_

#include <oatpp/web/server/handler/AuthorizationHandler.hpp>

/**
 * Implementation of a custom AuthorizationHandler to streamline the authorization process
 */
class MyAuthorization : public oatpp::web::server::handler::AuthorizationHandler {

 public:
  /**
   * Override the handleAuthorization method to use your own authorization process
   * @param header
   * @return
   */
  std::shared_ptr<oatpp::web::server::handler::AuthorizationObject> handleAuthorization(const oatpp::String &header) override;
};

/**
 * Implementation of a custom AuthorizationObject to add further fields/methods
 */
class MyAuthorizationObject : public oatpp::web::server::handler::AuthorizationObject {
 public:
  oatpp::Int64 id;
  oatpp::String email;

  bool isAdmin();
};

#endif //AUTHORIZATION_EXAMPLE_SRC_LIB_MYAUTHORIZATION_HPP_
