This repo demonstrates a bug in the FMinimalReplicationTagCountMap::NetSerialize function where loose gameplay tag counts are always set to 1 during replication, regardless of their actual count on the server.
This creates a desync with the gameplay tags applied to a player in the client

Video: https://youtu.be/RhCOaVvR844

### Steps to reproduce

Playing as client:
1. The project has a character with an ability system component and two abilities:
   - GA_DummyAbility that grants the Debug.Test gameplay tag via ActivationOwnedTags
   - GA_PlayMontage that plays a montage but is blocked by Debug.Test
2. It also has a trigger that runs AddLooseGameplayTags with the Debug.Test tag when a player enters it (just on the server)
3. If the player activates GA_DummyAbility outside the trigger (gaining the Debug.Test tag), then enters the trigger:
   - The server correctly adds another Debug.Test tag (count = 2)
   - But clients receive a count of 1 due to the hardcoded line in NetSerialize
4. When GA_DummyAbility ends and removes its tag:
   - The server correctly has a count of 1 from the trigger
   - But clients drop to 0, creating a desync
   
