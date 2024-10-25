// These macros can only be used within the scope of a CBaseBot

#ifdef TWBL_DEBUG
#define Die(comment) _Die(comment)
#define Emote(value, comment) _Emote(value, comment)
#define Aim(TargetX, TargetY, comment) _Aim(TargetX, TargetY, comment, __func__, __FILE__, __LINE__)
#define AimPos(TargetX, TargetY, comment) _AimPos(TargetX, TargetY, comment, __func__, __FILE__, __LINE__)
#define SetDirection(value, comment) _SetDirection(value, comment, __func__, __FILE__, __LINE__)
#define Hook(value, comment) _Hook(value, comment, __func__, __FILE__, __LINE__)
#define Jump(value, comment) _Jump(value, comment, __func__, __FILE__, __LINE__)
#define Fire(value, comment) _Fire(value, comment, __func__, __FILE__, __LINE__)
#define SetWeapon(value, comment) _SetWeapon(value, comment, __func__, __FILE__, __LINE__)
#else
#define Die(comment) _DieRaw()
#define Emote(value, comment) _EmoteRaw()
#define Aim(TargetX, TargetY, comment) _AimRaw(TargetX, TargetY)
#define AimPos(TargetX, TargetY, comment) _AimPosRaw(TargetX, TargetY)
#define SetDirection(value, comment) _SetDirectionRaw(value)
#define Hook(value, comment) _HookRaw(value)
#define Jump(value, comment) _JumpRaw(value)
#define Fire(value, comment) _FireRaw(value)
#define SetWeapon(value, comment) _SetWeaponRaw(value)
#endif

#define Left(comment) SetDirection(-1, comment)
#define Right(comment) SetDirection(1, comment)
