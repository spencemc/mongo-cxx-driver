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

#pragma once

#include <memory>

#include <bsoncxx/document/view.hpp>

#include <mongocxx/config/prelude.hpp>

namespace mongocxx {
MONGOCXX_INLINE_NAMESPACE_BEGIN

namespace options {
class MONGOCXX_PRIVATE apm_wrapper;
}

namespace apm {

class MONGOCXX_API command_succeeded_event {
   public:
    ///
    /// Destroys a command_succeeded_event.
    ///
    ~command_succeeded_event();

    ///
    /// Returns the server reply for the succeeded operation.
    ///
    /// @return A document view containing the reply.
    ///
    bsoncxx::document::view reply() const;

    ///
    /// Returns the name of the command.
    ///
    /// @return A string view with the command name.
    ///
    bsoncxx::stdx::string_view command_name() const;

    ///
    /// Returns the duration of the successful operation.
    ///
    /// @return An int64_t with the duration in microseconds.
    ///
    std::int64_t duration() const;

    ///
    /// Returns the request id.
    ///
    /// @return An int64_t with the request id.
    ///
    std::int64_t request_id() const;

    ///
    /// Returns the operation id.
    ///
    /// @return An int64_t with the operation id.
    ///
    std::int64_t operation_id() const;

    ///
    /// Returns the host name.
    ///
    /// @return A string view with the host name.
    ///
    bsoncxx::stdx::string_view host() const;

    ///
    /// Returns the port.
    ///
    /// @return A uint16_t with the port.
    ///
    std::uint16_t port() const;

   private:
    friend class options::apm_wrapper;
    class MONGOCXX_PRIVATE impl;
    MONGOCXX_PRIVATE explicit command_succeeded_event(const void* event);
    std::unique_ptr<impl> _impl;
};

}  // namespace apm
MONGOCXX_INLINE_NAMESPACE_END
}  // namespace mongocxx

#include <mongocxx/config/postlude.hpp>
