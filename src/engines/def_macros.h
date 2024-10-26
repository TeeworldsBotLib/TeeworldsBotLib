// These macros can only be used within the scope of a CBaseEngine

#ifdef TWBL_DEBUG
#define Die(comment) Bot()->_Die(comment)
#define Emote(value, comment) Bot()->_Emote(value, comment)
#define Aim(TargetX, TargetY, comment) Bot()->_Aim(TargetX, TargetY, comment, __func__, __FILE__, __LINE__)
#define AimPos(TargetX, TargetY, comment) Bot()->_AimPos(TargetX, TargetY, comment, __func__, __FILE__, __LINE__)
#define SetDirection(value, comment) Bot()->_SetDirection(value, comment, __func__, __FILE__, __LINE__)
#define Hook(value, comment) Bot()->_Hook(value, comment, __func__, __FILE__, __LINE__)
#define Jump(value, comment) Bot()->_Jump(value, comment, __func__, __FILE__, __LINE__)
#define Fire(value, comment) Bot()->_Fire(value, comment, __func__, __FILE__, __LINE__)
#define SetWeapon(value, comment) Bot()->_SetWeapon(value, comment, __func__, __FILE__, __LINE__)
#else
#define Die(comment) Bot()->_DieRaw()
#define Emote(value, comment) Bot()->_EmoteRaw(value)
#define Aim(TargetX, TargetY, comment) Bot()->_AimRaw(TargetX, TargetY)
#define AimPos(TargetX, TargetY, comment) Bot()->_AimPosRaw(TargetX, TargetY)
#define SetDirection(value, comment) Bot()->_SetDirectionRaw(value)
#define Hook(value, comment) Bot()->_HookRaw(value)
#define Jump(value, comment) Bot()->_JumpRaw(value)
#define Fire(value, comment) Bot()->_FireRaw(value)
#define SetWeapon(value, comment) Bot()->_SetWeaponRaw(value)
#endif

#define Left(comment) SetDirection(-1, comment)
#define Right(comment) SetDirection(1, comment)
