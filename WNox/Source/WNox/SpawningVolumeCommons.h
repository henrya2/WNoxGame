#pragma once

DECLARE_MULTICAST_DELEGATE_OneParam(FOnSpawnedActorDisappearMultiDelegate, class AActor*);
DECLARE_DELEGATE_OneParam(FOnSpawnedActorDisappearDelegate, class AActor*);