// Copyright 2018-present MongoDB Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
// http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include <mongocxx/events/command_started_event.hpp>

#include <bsoncxx/stdx/make_unique.hpp>
#include <mongocxx/events/private/command_started_event.hh>
#include <mongocxx/private/libmongoc.hh>

#include <mongocxx/config/private/prelude.hh>

namespace mongocxx {
MONGOCXX_INLINE_NAMESPACE_BEGIN
namespace events {

command_started_event::command_started_event(const void* event)
    : _impl(bsoncxx::stdx::make_unique<impl>(
          static_cast<const mongoc_apm_command_started_t*>(event))) {}

command_started_event::~command_started_event() = default;

bsoncxx::document::view command_started_event::command() const {
    auto command = libmongoc::apm_command_started_get_command(_impl->started_event);
    return {bson_get_data(command), command->len};
}

bsoncxx::stdx::string_view command_started_event::database_name() const {
    return libmongoc::apm_command_started_get_database_name(_impl->started_event);
}

bsoncxx::stdx::string_view command_started_event::command_name() const {
    return libmongoc::apm_command_started_get_command_name(_impl->started_event);
}

std::int64_t command_started_event::request_id() const {
    return libmongoc::apm_command_started_get_request_id(_impl->started_event);
}

std::int64_t command_started_event::operation_id() const {
    return libmongoc::apm_command_started_get_operation_id(_impl->started_event);
}

bsoncxx::stdx::string_view command_started_event::host() const {
    return libmongoc::apm_command_started_get_host(_impl->started_event)->host;
}

std::uint16_t command_started_event::port() const {
    return libmongoc::apm_command_started_get_host(_impl->started_event)->port;
}

}  // namespace events
MONGOCXX_INLINE_NAMESPACE_END
}  // namespace mongocxx
