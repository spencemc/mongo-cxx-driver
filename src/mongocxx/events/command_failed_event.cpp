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

#include <mongocxx/events/command_failed_event.hpp>

#include <bsoncxx/stdx/make_unique.hpp>
#include <mongocxx/events/private/command_failed_event.hh>
#include <mongocxx/private/libmongoc.hh>

#include <mongocxx/config/private/prelude.hh>

namespace mongocxx {
MONGOCXX_INLINE_NAMESPACE_BEGIN
namespace events {

command_failed_event::command_failed_event(const void* event)
    : _impl(bsoncxx::stdx::make_unique<impl>((mongoc_apm_command_failed_t*)event)) {}

command_failed_event::~command_failed_event() = default;

bsoncxx::document::view command_failed_event::failure() const {
    auto failure = libmongoc::apm_command_failed_get_reply(_impl->failed_event_t);
    return {bson_get_data(failure), failure->len};
}

bsoncxx::stdx::string_view command_failed_event::command_name() const {
    return libmongoc::apm_command_failed_get_command_name(_impl->failed_event_t);
}

std::int64_t command_failed_event::duration() const {
    return libmongoc::apm_command_failed_get_duration(_impl->failed_event_t);
}

std::int64_t command_failed_event::request_id() const {
    return libmongoc::apm_command_failed_get_request_id(_impl->failed_event_t);
}

std::int64_t command_failed_event::operation_id() const {
    return libmongoc::apm_command_failed_get_operation_id(_impl->failed_event_t);
}

bsoncxx::stdx::string_view command_failed_event::host() const {
    return libmongoc::apm_command_failed_get_host(_impl->failed_event_t)->host;
}

std::uint16_t command_failed_event::port() const {
    return libmongoc::apm_command_failed_get_host(_impl->failed_event_t)->port;
}

}  // namespace events
MONGOCXX_INLINE_NAMESPACE_END
}  // namespace mongocxx
