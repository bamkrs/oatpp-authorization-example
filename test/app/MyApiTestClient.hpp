//
// Created by Leonid on 2019-06-06.
//

#ifndef MyApiTestClient_hpp
#define MyApiTestClient_hpp

#include "oatpp/web/client/ApiClient.hpp"
#include "oatpp/core/macro/codegen.hpp"
#include "oatpp/encoding/Base64.hpp"

/* Begin Api Client code generation */
#include OATPP_CODEGEN_BEGIN(ApiClient)

/**
 * Test API client.
 * Use this client to call application APIs.
 */
class MyApiTestClient : public oatpp::web::client::ApiClient {

  API_CLIENT_INIT(MyApiTestClient)

  API_CALL("GET", "/", getRoot)
  API_CALL("GET", "/whoami", whoami, AUTHORIZATION(String, authorization))
  API_CALL("GET", "/secret", secret, AUTHORIZATION(String, authorization))
  API_CALL("GET", "/moresecret", moreSecret, AUTHORIZATION(String, authorization))
  // TODO - add more client API calls here

};

/* End Api Client code generation */
#include OATPP_CODEGEN_END(ApiClient)

#endif // MyApiTestClient_hpp
