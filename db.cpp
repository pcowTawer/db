#include <cstdint>
#include <iostream>
#include <vector>
#include "bsoncxx/json.hpp"
#include "mongocxx/client.hpp"
#include "mongocxx/stdx.hpp"
#include "mongocxx/uri.hpp"
#include "mongocxx/instance.hpp"
#include "bsoncxx/builder/stream/helpers.hpp"
#include "bsoncxx/builder/stream/document.hpp"
#include "bsoncxx/builder/stream/array.hpp"


using bsoncxx::builder::stream::close_array;
using bsoncxx::builder::stream::close_document;
using bsoncxx::builder::stream::document;
using bsoncxx::builder::stream::finalize;
using bsoncxx::builder::stream::open_array;
using bsoncxx::builder::stream::open_document;

int main()
{
    mongocxx::instance instace{};
    mongocxx::uri uri("mongodb://localhost:27017");//Connecting to mongodb
    mongocxx::client client(uri);
    mongocxx::database db = client["mydatabase"]; //Connecting to mydatabase
    mongocxx::collection coll = db["mycollection"]; //Conneting to collection in mydatabase
    auto builder = bsoncxx::builder::stream::document{};//Creating builder that creates document
    //Writing data to document
    bsoncxx::document::value doc_value = builder
    << "name" << "MongoDB"
    << "type" << "database"
    << "count" << 1
    << "versions" << bsoncxx::builder::stream::open_array
    << "v3.2" << "v3.0" << "v2.6"
    << close_array
    << "info" << bsoncxx::builder::stream::open_document
    << "x" << 203
    << "y" << 102
    << bsoncxx::builder::stream::close_document
    << bsoncxx::builder::stream::finalize;

    // std::vector<bsoncxx::document::value> documents;
    // for(int i = 0; i < 100; i++) {
    //     documents.push_back(
    //    bsoncxx::builder::stream::document{} << "i" << i << finalize);
    // }
    bsoncxx::document::view view = doc_value.view();
    coll.insert_one(view);

    // mongocxx::cursor cursor = coll.find({});
    // for(auto doc : cursor) {
    //   std::cout << bsoncxx::to_json(doc) << "/n";
    // }
    // coll.insert_many(documents);
    return 0;
}