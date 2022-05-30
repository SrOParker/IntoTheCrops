
#pragma once

#include "../../cmp/CAnimation.hpp"
#include "../../cmp/CInformation.hpp"
#include "../../cmp/CRenderGL.hpp"
#include "../../cmp/CPhysics.hpp"
#include "../../cmp/CInput.hpp"
#include "../../cmp/tags.hpp"
#include "../../cmp/CCamera.hpp"
#include "../../cmp/CIA.hpp"
#include "../../cmp/CDirectionalLight.hpp"
#include "../../cmp/CPointLight.hpp"
#include "../../cmp/CSound.hpp"
#include "../../cmp/CCollision.hpp"
#include "../../cmp/CPng.hpp"
#include "../../cmp/CHealth.hpp"
#include "../../cmp/CStamina.hpp"
#include "../../cmp/CIDLvl.hpp"
#include "../../cmp/CReference.hpp"
#include "../../cmp/CMap.hpp"
#include "../../cmp/CReposition.hpp"
#include "../entitymanager.hpp"


//ADD +1
//TAGS : 34
//CMPS : 16 
using TagList = 
Typelist<TPlayer
        , TEnemy
        , THealth
        , TInstance
        , TCollider
        , TCollisionable
        , TNotRenderizable
        , TWall
        , Tpickable
        , TSEvent
        , TDoor
        , TDoorKeyChurch
        , TBurnable
        , TTransition
        , TDescription
        , TScaleBoundingBox
        , TBoundingBoxHelp
        , TYesquero
        , TLantern
        , TReposition
        , TSaveStatus
        , TWindowMailBox
        , TMailBox
        , TBackDoor
        , TBedRoom
        , TFuse
        , TFuseBox
        , TPhone
        , TObjectInteractuable
        , TPainting
        , TFarmer
        , TAnimated
        , TDummy
        , TTombEvent
        , TEnemyEvent
        , TTransitionY
        , TSaveBox
        , TCodeLock
        , TRing
        , TShears
        , THatch
        , TMarco
        , TJumpscare
        , TRueda
        , TEventDoorGranero
        , TNotPatrol
        , TCarEventFinal
        , TNotRenderAnim
        , TYesqueroPermanente
        >;
using ComponentList = 
Typelist<CInformation
        , CRenderGL
        , CPhysics
        , CInput
        , CCamera
        , CIA
        , CDirectionalLight
        , CPointLight
        , CCollision
        , CSound
        , CPng
        , CHealth
        , CStamina
        , CIDLvl
        , CReference
        , CMap
        , CReposition
        , CAnimation
        >;

using Manentity_type = ManEntity<ComponentList, TagList, 100>;
using Entity = Manentity_type::Entity;

