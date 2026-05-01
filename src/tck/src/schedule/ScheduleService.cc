// SPDX-License-Identifier: Apache-2.0
#include "schedule/ScheduleService.h"
#include "common/CommonTransactionParams.h"
#include "schedule/params/DeleteScheduleParams.h"
#include "sdk/SdkClient.h"

#include <ScheduleDeleteTransaction.h>
#include <ScheduleId.h>
#include <TransactionReceipt.h>
#include <TransactionResponse.h>

#include <nlohmann/json.hpp>

namespace Hiero::TCK::ScheduleService
{
//-----
nlohmann::json deleteSchedule(const DeleteScheduleParams& params)
{
  ScheduleDeleteTransaction scheduleDeleteTransaction;
  scheduleDeleteTransaction.setGrpcDeadline(SdkClient::DEFAULT_TCK_REQUEST_TIMEOUT);

  if (params.mScheduleId.has_value())
  {
    scheduleDeleteTransaction.setScheduleId(ScheduleId::fromString(params.mScheduleId.value()));
  }

  if (params.mCommonTxParams.has_value())
  {
    params.mCommonTxParams->fillOutTransaction(scheduleDeleteTransaction, SdkClient::getClient());
  }

  return {
    {"status",
     gStatusToString.at(
        scheduleDeleteTransaction.execute(SdkClient::getClient()).getReceipt(SdkClient::getClient()).mStatus)},
  };
}

} // namespace Hiero::TCK::ScheduleService
