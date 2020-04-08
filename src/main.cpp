#include "../include/main.hpp"
#include "../extern/beatsaber-hook/shared/customui/customui.hpp"
#include "../extern/beatsaber-hook/shared/config/config-utils.hpp"

#include <iostream> 
#include <string.h>

Il2CppObject* posXSlider;//The X slider
Il2CppObject* posYSlider;//The Y slider
Il2CppObject* posZSlider;//The Z slider

Il2CppObject* rotXSlider;//The X slider
Il2CppObject* rotYSlider;//The Y slider
Il2CppObject* rotZSlider;//The Z slider

float xSliderValue;//The X slider value
float ySliderValue;//The Y slider value
float zSliderValue;//The Z slider value

float rotXSliderValue;//The X slider value
float rotYSliderValue;//The Y slider value
float rotZSliderValue;//The Z slider value

bool leftHand;
bool noArrows;
bool oneSaber;

int extraSettingAmount = 41;

float num = 50.0f;//This will be the maximum value of the sliders

int triggerNode;
float rTriggerVal;
float lTriggerVal;
bool triggerReady = true;

bool darthMaul = false;

bool inSong = false;
bool inSettings = false;

bool pauseChange;

Il2CppObject* mainSettingsModel;

CustomUI::TextObject settingsText;

static void CheckRegenConfig(ConfigDocument& config) {
    if (!config.HasMember("xSliderValue")) {
        log(WARNING, "Regenerating config!");
        config.SetObject();
        auto& allocator = config.GetAllocator();
        config.AddMember("xSliderValue", 0.0, allocator);
        config.AddMember("ySliderValue", 0.0, allocator);
        config.AddMember("zSliderValue", 0.0, allocator);
        config.AddMember("rotXSliderValue", 0.0, allocator);
        config.AddMember("rotYSliderValue", 0.0, allocator);
        config.AddMember("rotZSliderValue", 0.0, allocator);

        config.AddMember("xSliderValueD", 0.0, allocator);
        config.AddMember("ySliderValueD", 0.0, allocator);
        config.AddMember("zSliderValueD", 0.0, allocator);
        config.AddMember("rotXSliderValueD", 0.0, allocator);
        config.AddMember("rotYSliderValueD", 0.0, allocator);
        config.AddMember("rotZSliderValueD", 0.0, allocator);
        Configuration::Write();
        log(INFO, "Config regeneration complete!");
    }
    else {
        log(INFO, "Not regnerating config.");
    }
}

static auto& config = Configuration::config;

static void InitConfig() {
    Configuration::Load();
    CheckRegenConfig(config);
}

static void ReloadConfig() {
    Configuration::Reload();
    CheckRegenConfig(config);
}


MAKE_HOOK_OFFSETLESS(Install, void, Il2CppObject* self) {

    mainSettingsModel = *CRASH_UNLESS(il2cpp_utils::GetFieldValue(self, "_mainSettingsModel"));

    Install(self);
}

MAKE_HOOK_OFFSETLESS(DidActivate, void, Il2CppObject* self, bool firstActivation, int activationType) {//Called when entering the controllers section of the settings menu

    DidActivate(self, firstActivation, activationType);//Calling the function before changing everything so that the changes stay the same

    inSettings = true;

    float num2 = -num;//This will be the minimum value the sliders (set to negative of num)
    int numberOfSteps = ((num - num2) / 0.1f) + 1;//Finding the number of steps

    posXSlider = *CRASH_UNLESS(il2cpp_utils::GetFieldValue(self, "_posXSlider"));//Finding the position X slider
    posYSlider = *CRASH_UNLESS(il2cpp_utils::GetFieldValue(self, "_posYSlider"));//Finding the position Y slider
    posZSlider = *CRASH_UNLESS(il2cpp_utils::GetFieldValue(self, "_posZSlider"));//Finding the position Z slider

    rotXSlider = *CRASH_UNLESS(il2cpp_utils::GetFieldValue(self, "_rotXSlider"));//Finding the position X slider
    rotYSlider = *CRASH_UNLESS(il2cpp_utils::GetFieldValue(self, "_rotYSlider"));//Finding the position Y slider
    rotZSlider = *CRASH_UNLESS(il2cpp_utils::GetFieldValue(self, "_rotZSlider"));//Finding the position Z slider

    //Setting the properties of X slider
    il2cpp_utils::RunMethod(posXSlider, "set_maxValue", num);//Changing the max value to num
    il2cpp_utils::RunMethod(posXSlider, "set_minValue", num2);//Changing the minumum value to negative of num
    il2cpp_utils::RunMethod(posXSlider, "set_numberOfSteps", numberOfSteps);//Making it so the steps still go by tenths

    //Setting the properties of Y slider
    il2cpp_utils::RunMethod(posYSlider, "set_maxValue", num);//Changing the max value to num
    il2cpp_utils::RunMethod(posYSlider, "set_minValue", num2);//Changing the minumum value to negative of num
    il2cpp_utils::RunMethod(posYSlider, "set_numberOfSteps", numberOfSteps);//Making it so the steps still go by tenths

    //Setting the properties of Z slider
    il2cpp_utils::RunMethod(posZSlider, "set_maxValue", num);//Changing the max value to num
    il2cpp_utils::RunMethod(posZSlider, "set_minValue", num2);//Changing the minumum value to negative of num
    il2cpp_utils::RunMethod(posZSlider, "set_numberOfSteps", numberOfSteps);//Making it so the steps still go by tenths

    if (noArrows) {
        xSliderValue = config["xSliderValueD"].GetFloat();
        ySliderValue = config["ySliderValueD"].GetFloat();
        zSliderValue = config["zSliderValueD"].GetFloat();

        rotXSliderValue = config["rotXSliderValueD"].GetFloat();
        rotYSliderValue = config["rotYSliderValueD"].GetFloat();
        rotZSliderValue = config["rotZSliderValueD"].GetFloat();

        log(INFO, "Set values to darth");
    }
    else {
        xSliderValue = config["xSliderValue"].GetFloat();
        ySliderValue = config["ySliderValue"].GetFloat();
        zSliderValue = config["zSliderValue"].GetFloat();

        rotXSliderValue = config["rotXSliderValue"].GetFloat();
        rotYSliderValue = config["rotYSliderValue"].GetFloat();
        rotZSliderValue = config["rotZSliderValue"].GetFloat();

        log(INFO, "Set values to dual");
    }

    il2cpp_utils::RunMethod(posXSlider, "set_value", xSliderValue);//Setting the X slider value to xSliderValue
    il2cpp_utils::RunMethod(posYSlider, "set_value", ySliderValue);//Setting the Y slider value to ySliderValue
    il2cpp_utils::RunMethod(posZSlider, "set_value", zSliderValue);//Setting the Z slider value to zSliderValue

    il2cpp_utils::RunMethod(rotXSlider, "set_value", rotXSliderValue);//Setting the X slider value to xSliderValue
    il2cpp_utils::RunMethod(rotYSlider, "set_value", rotYSliderValue);//Setting the Y slider value to ySliderValue
    il2cpp_utils::RunMethod(rotZSlider, "set_value", rotZSliderValue);//Setting the Z slider value to zSliderValue

    il2cpp_utils::RunMethod(mainSettingsModel, "Load", true);

    auto* settingsTransform = *CRASH_UNLESS(il2cpp_utils::RunMethod(posXSlider, "get_transform"));
    auto* sliderParent = *CRASH_UNLESS(il2cpp_utils::RunMethod(settingsTransform, "GetParent"));
    auto* settingsParent = *CRASH_UNLESS(il2cpp_utils::RunMethod(sliderParent, "GetParent"));

    log(DEBUG, "%i", noArrows);

    if (noArrows) {
        settingsText.text = "<align=center>You are in Darth Maul settings";
    }
    else {
        settingsText.text = "<align=center>You are in Dual Saber settings";
    }
    settingsText.fontSize = 5.0F;
    settingsText.parentTransform = settingsParent;
    settingsText.sizeDelta = { 0, -200 };
    settingsText.create();
}

MAKE_HOOK_OFFSETLESS(ButtonDidActivate, void, Il2CppObject* self, int finishAction) {//Called when pressing any of the settings buttons ("Ok", "Cancel", and "Apply")

    if (finishAction == 0) {//Called when the "Ok" setting button is pressed
        log(INFO, "Ok Button Pressed");//Logging when the "Ok" setting button is pressed
    }
    else if (finishAction == 1) {//Called when the "Cancel" setting button is pressed
        log(INFO, "Cancel Button Pressed");//Logging when the "Cancel" setting button is pressed
    }
    else if (finishAction == 2) {//Called when the "Apply" setting button is pressed
        log(INFO, "Apply Button Pressed");//Logging when the "Apply" setting button is pressed
    }

    inSettings = false;

    if (finishAction == 0 || finishAction == 2) {
        xSliderValue = *CRASH_UNLESS(il2cpp_utils::RunMethod<float>(posXSlider, "get_value"));//Getting the value of the X Slider and setting it to xSliderValue
        ySliderValue = *CRASH_UNLESS(il2cpp_utils::RunMethod<float>(posYSlider, "get_value"));//Getting the value of the Y Slider and setting it to ySliderValue
        zSliderValue = *CRASH_UNLESS(il2cpp_utils::RunMethod<float>(posZSlider, "get_value"));//Getting the value of the Z Slider and setting it to zSliderValue

        rotXSliderValue = *CRASH_UNLESS(il2cpp_utils::RunMethod<float>(rotXSlider, "get_value"));//Getting the value of the X Slider and setting it to xSliderValue
        rotYSliderValue = *CRASH_UNLESS(il2cpp_utils::RunMethod<float>(rotYSlider, "get_value"));//Getting the value of the Y Slider and setting it to ySliderValue
        rotZSliderValue = *CRASH_UNLESS(il2cpp_utils::RunMethod<float>(rotZSlider, "get_value"));//Getting the value of the Z Slider and setting it to zSliderValue


        if (!noArrows) {
            float storedX = config["xSliderValueD"].GetFloat();
            float storedY = config["ySliderValueD"].GetFloat();
            float storedZ = config["zSliderValueD"].GetFloat();

            float storedXRot = config["rotXSliderValueD"].GetFloat();
            float storedYRot = config["rotYSliderValueD"].GetFloat();
            float storedZRot = config["rotZSliderValueD"].GetFloat();

            config.SetObject();
            auto& allocator = config.GetAllocator();
            config.AddMember("xSliderValue", xSliderValue, allocator);
            config.AddMember("ySliderValue", ySliderValue, allocator);
            config.AddMember("zSliderValue", zSliderValue, allocator);
            config.AddMember("rotXSliderValue", rotXSliderValue, allocator);
            config.AddMember("rotYSliderValue", rotYSliderValue, allocator);
            config.AddMember("rotZSliderValue", rotZSliderValue, allocator);

            config.AddMember("xSliderValueD", storedX, allocator);
            config.AddMember("ySliderValueD", storedY, allocator);
            config.AddMember("zSliderValueD", storedZ, allocator);
            config.AddMember("rotXSliderValueD", storedXRot, allocator);
            config.AddMember("rotYSliderValueD", storedYRot, allocator);
            config.AddMember("rotZSliderValueD", storedZRot, allocator);
            Configuration::Write();
        }
        else {
            float storedX = config["xSliderValue"].GetFloat();
            float storedY = config["ySliderValue"].GetFloat();
            float storedZ = config["zSliderValue"].GetFloat();

            float storedXRot = config["rotXSliderValue"].GetFloat();
            float storedYRot = config["rotYSliderValue"].GetFloat();
            float storedZRot = config["rotZSliderValue"].GetFloat();

            config.SetObject();
            auto& allocator = config.GetAllocator();
            config.AddMember("xSliderValue", storedX, allocator);
            config.AddMember("ySliderValue", storedY, allocator);
            config.AddMember("zSliderValue", storedZ, allocator);
            config.AddMember("rotXSliderValue", storedXRot, allocator);
            config.AddMember("rotYSliderValue", storedYRot, allocator);
            config.AddMember("rotZSliderValue", storedZRot, allocator);

            config.AddMember("xSliderValueD", xSliderValue, allocator);
            config.AddMember("ySliderValueD", ySliderValue, allocator);
            config.AddMember("zSliderValueD", zSliderValue, allocator);
            config.AddMember("rotXSliderValueD", rotXSliderValue, allocator);
            config.AddMember("rotYSliderValueD", rotYSliderValue, allocator);
            config.AddMember("rotZSliderValueD", rotZSliderValue, allocator);
            Configuration::Write();
        }
    }

    noArrows = false;
    darthMaul = false;
    
    if (settingsText.gameObj != nullptr) {
        il2cpp_utils::RunMethod(il2cpp_utils::GetClassFromName("UnityEngine", "Object"), "Destroy", settingsText.gameObj);
    }

    ButtonDidActivate(self, finishAction);//Calling the function after having stored the slider values
}

MAKE_HOOK_OFFSETLESS(PlayerController_Update, void, Il2CppObject* self) {

    PlayerController_Update(self);//Calling the function before changing values

    if (lTriggerVal > 0.8f && rTriggerVal > 0.8f && triggerReady && noArrows && !oneSaber) {
        if (darthMaul) {
            darthMaul = false;
        }
        else {
            darthMaul = true;
        }
        triggerReady = false;
        il2cpp_utils::RunMethod(mainSettingsModel, "Load", true);
    }

    if (lTriggerVal == 0 && rTriggerVal == 0 && !triggerReady) {
        triggerReady = true;
    }

    Il2CppObject* leftSaber = *il2cpp_utils::GetFieldValue(self, "_leftSaber");
    Il2CppObject* rightSaber = *il2cpp_utils::GetFieldValue(self, "_rightSaber");

    if(leftSaber != nullptr && rightSaber != nullptr) {
        Il2CppObject* leftSaberTransform = nullptr;
        Il2CppObject* rightSaberTransform = nullptr;

        Il2CppClass* componentsClass = il2cpp_utils::GetClassFromName("", "Saber");
        leftSaberTransform = *il2cpp_utils::RunMethod(leftSaber, il2cpp_functions::class_get_method_from_name(componentsClass, "get_transform", 0));
        rightSaberTransform = *il2cpp_utils::RunMethod(rightSaber, il2cpp_functions::class_get_method_from_name(componentsClass, "get_transform", 0));

        if(leftSaberTransform != nullptr && rightSaberTransform != nullptr) {
            Il2CppClass* transformClass = il2cpp_utils::GetClassFromName("UnityEngine", "Transform");
            const MethodInfo* getMethod = il2cpp_functions::class_get_method_from_name(transformClass, "get_localPosition", 0);
            const MethodInfo* setMethod = il2cpp_functions::class_get_method_from_name(transformClass, "set_localPosition", 1);
            const MethodInfo* setRotate = il2cpp_functions::class_get_method_from_name(transformClass, "Rotate", 1);
            const MethodInfo* setTranslate = il2cpp_functions::class_get_method_from_name(transformClass, "Translate", 1);
            const MethodInfo* getLocalRotation = il2cpp_functions::class_get_method_from_name(transformClass, "get_localRotation", 0);
            const MethodInfo* setLocalRotation = il2cpp_functions::class_get_method_from_name(transformClass, "set_localRotation", 1);

            Vector3 rightSaberLocalPosition = *il2cpp_utils::RunMethod<Vector3>(rightSaberTransform, getMethod);;
            Vector3 leftSaberLocalPosition = *il2cpp_utils::RunMethod<Vector3>(leftSaberTransform, getMethod);
            
            Quaternion rightSaberLocalRotation = *il2cpp_utils::RunMethod<Quaternion>(rightSaberTransform, getLocalRotation);
            Quaternion leftSaberLocalRotation = *il2cpp_utils::RunMethod<Quaternion>(leftSaberTransform, getLocalRotation);

            if (darthMaul && !oneSaber) {
                if (!leftHand) {
                    il2cpp_utils::RunMethod(rightSaberTransform, setTranslate, Vector3{ 0, 0, -0.27f });
                    il2cpp_utils::RunMethod(rightSaberTransform, setRotate, Vector3{ 0, 180, 0 });
                    il2cpp_utils::RunMethod(leftSaberTransform, setMethod, rightSaberLocalPosition);
                    il2cpp_utils::RunMethod(leftSaberTransform, setLocalRotation, rightSaberLocalRotation);
                    il2cpp_utils::RunMethod(leftSaberTransform, setTranslate, Vector3{ 0, 0, 0.07f });
                }
                else {
                    il2cpp_utils::RunMethod(leftSaberTransform, setTranslate, Vector3{ 0, 0, -0.27f });
                    il2cpp_utils::RunMethod(leftSaberTransform, setRotate, Vector3{ 0, 180, 0 });
                    il2cpp_utils::RunMethod(rightSaberTransform, setMethod, leftSaberLocalPosition);
                    il2cpp_utils::RunMethod(rightSaberTransform, setLocalRotation, leftSaberLocalRotation);
                    il2cpp_utils::RunMethod(rightSaberTransform, setTranslate, Vector3{ 0, 0, 0.07f });
                }
            }
        }
    }
}

MAKE_HOOK_OFFSETLESS(HapticFeedbackController_Rumble, void, Il2CppObject* self, int node, float strength) {

    if (darthMaul) {
        if (!leftHand) {
            node = 5;
        }
        else {
            node = 4;
        }
    }

    HapticFeedbackController_Rumble(self, node, strength);
}

MAKE_HOOK_OFFSETLESS(PlayerSettingsStart, void, Il2CppObject* self, int* idx, int* numberOfElements) {

    Array<float>* valuesArray = reinterpret_cast<Array<float>*>(il2cpp_functions::array_new(il2cpp_utils::GetClassFromName("System", "Single"), 10 + extraSettingAmount));

    Array<float>* value = *CRASH_UNLESS(il2cpp_utils::GetFieldValue<Array<float>*>(self, "_values"));

    for (int i = 0; i < value->Length(); i++) {
        valuesArray->values[i] = value->values[i];
    }

    for (int i = 0; i <= extraSettingAmount; i++) {
        valuesArray->values[11 + i] = 1.0f + (i * 0.1f);
    }

    il2cpp_utils::SetFieldValue(self, "_values", valuesArray);

    PlayerSettingsStart(self, idx, numberOfElements);
}

MAKE_HOOK_OFFSETLESS(Refresh, void, Il2CppObject* self) {

    Refresh(self);

    //Il2CppObject* GetGameObject;
    std::string NoArrow = "NoArrows";
    std::string GameObjectString;
    //Il2CppString* GameObjectName;

    Il2CppObject* GMT_nameText;
    Il2CppString* textToSet;

    auto* GetGameObject = *CRASH_UNLESS(il2cpp_utils::RunMethod(self, "get_gameObject"));

    //if (GetGameObject != nullptr) {
        auto* GameObjectName = *CRASH_UNLESS(il2cpp_utils::RunMethod<Il2CppString*>(il2cpp_utils::GetClassFromName("UnityEngine", "Object"), "GetName", GetGameObject));
    //}
    if (GameObjectName != nullptr) {
        GameObjectString = to_utf8(csstrtostr(GameObjectName));

        if (GameObjectString == NoArrow) {
            textToSet = il2cpp_utils::createcsstr("<size=90%>No Arrows/Darth Maul Mode</size>\n<color=#ffffff88><size=80%>-0.30</size></color>");
            GMT_nameText = *CRASH_UNLESS(il2cpp_utils::GetFieldValue(self, "_nameText"));
            if (!il2cpp_utils::RunMethod(GMT_nameText, "set_text", textToSet)) {
                log(ERROR, "Failed to set text");
            }
        }
    }
}

MAKE_HOOK_OFFSETLESS(SongStart, void, Il2CppObject* self, Il2CppObject* difficultyBeatmap, Il2CppObject* overrideEnvironmentSettings, Il2CppObject* overrideColorScheme, Il2CppObject* gameplayModifiers, Il2CppObject* playerSpecificSettings, Il2CppObject* practiceSettings, Il2CppString* backButtonText, bool useTestNoteCutSoundEffects) {

    inSong = true;
    leftHand = *il2cpp_utils::RunMethod<bool>(playerSpecificSettings, "get_leftHanded");

    darthMaul = noArrows;

    il2cpp_utils::RunMethod(mainSettingsModel, "Load", true);

    SongStart(self, difficultyBeatmap, overrideEnvironmentSettings, overrideColorScheme, gameplayModifiers, playerSpecificSettings, practiceSettings, backButtonText, useTestNoteCutSoundEffects);
}

MAKE_HOOK_OFFSETLESS(SongFinish, void, Il2CppObject* self, Il2CppObject* levelCompletionResults) {

    inSong = false;

    darthMaul = false;

    log(INFO, "Song has ended");

    il2cpp_utils::RunMethod(mainSettingsModel, "Load", true);

    SongFinish(self, levelCompletionResults);
}

MAKE_HOOK_OFFSETLESS(ModifierChanged, void, Il2CppObject* self, Il2CppObject* gameplayModifiers, Il2CppObject* gameplayModifierParams, bool value) {

    ModifierChanged(self, gameplayModifiers, gameplayModifierParams, value);

    noArrows = *il2cpp_utils::RunMethod<bool>(gameplayModifiers, "get_noArrows");

    log(INFO, "%i", noArrows);
}

MAKE_HOOK_OFFSETLESS(SettingsLoad, void, Il2CppObject* self, bool forced) {

    SettingsLoad(self, forced);

    auto* controllerPos = *CRASH_UNLESS(il2cpp_utils::GetFieldValue(self, "controllerPosition"));
    auto* controllerRot = *CRASH_UNLESS(il2cpp_utils::GetFieldValue(self, "controllerRotation"));

    if ((inSong && darthMaul && !oneSaber) || (inSettings && noArrows && !oneSaber)) {
        xSliderValue = config["xSliderValueD"].GetFloat();
        ySliderValue = config["ySliderValueD"].GetFloat();
        zSliderValue = config["zSliderValueD"].GetFloat();

        rotXSliderValue = config["rotXSliderValueD"].GetFloat();
        rotYSliderValue = config["rotYSliderValueD"].GetFloat();
        rotZSliderValue = config["rotZSliderValueD"].GetFloat();

        Vector3 value = Vector3{ xSliderValue / 100, ySliderValue / 100, zSliderValue / 100 + (0.07f) };
        if (leftHand) {
            value.x = -(xSliderValue / 100);
        }
        il2cpp_utils::SetPropertyValue(controllerPos, "value", &value);

        value = Vector3{ rotXSliderValue, rotYSliderValue, -rotZSliderValue };
        il2cpp_utils::SetPropertyValue(controllerRot, "value", &value);
    }
    else {
        xSliderValue = config["xSliderValue"].GetFloat();
        ySliderValue = config["ySliderValue"].GetFloat();
        zSliderValue = config["zSliderValue"].GetFloat();

        rotXSliderValue = config["rotXSliderValue"].GetFloat();
        rotYSliderValue = config["rotYSliderValue"].GetFloat();
        rotZSliderValue = config["rotZSliderValue"].GetFloat();

        Vector3 value = Vector3{ xSliderValue / 100, ySliderValue / 100, zSliderValue / 100 };
        il2cpp_utils::SetPropertyValue(controllerPos, "value", &value);

        value = Vector3{ rotXSliderValue, rotYSliderValue, rotZSliderValue };
        il2cpp_utils::SetPropertyValue(controllerRot, "value", &value);
    }
    log(INFO, "Settings have loaded %i", noArrows);
}

MAKE_HOOK_OFFSETLESS(Triggers, void, Il2CppObject* self, int node) {

    triggerNode = node;

    Triggers(self, node);
}

MAKE_HOOK_OFFSETLESS(ControllerUpdate, void, Il2CppObject* self) {

    float trigger = *CRASH_UNLESS(il2cpp_utils::RunMethod<float>(self, "get_triggerValue"));

    if (triggerNode == 4) {
        lTriggerVal = trigger;
    }
    if (triggerNode == 5) {
        rTriggerVal = trigger;
    }

    ControllerUpdate(self);
}

MAKE_HOOK_OFFSETLESS(PauseStart, void, Il2CppObject* self) {

    if (darthMaul) {
        darthMaul = false;
        pauseChange = true;
    }

    il2cpp_utils::RunMethod(mainSettingsModel, "Load", true);

    PauseStart(self);
}

MAKE_HOOK_OFFSETLESS(PauseFinish, void, Il2CppObject* self) {

    if (pauseChange) {
        darthMaul = true;
        pauseChange = false;
    }

    il2cpp_utils::RunMethod(mainSettingsModel, "Load", true);

    PauseFinish(self);
}

MAKE_HOOK_OFFSETLESS(SettingsCell, void, Il2CppObject* self, int transitionType) {

    if (settingsText.gameObj != nullptr) {
        il2cpp_utils::RunMethod(il2cpp_utils::GetClassFromName("UnityEngine", "Object"), "Destroy", settingsText.gameObj);
    }

    SettingsCell(self, transitionType);
}

MAKE_HOOK_OFFSETLESS(OneSaberCheck, void, Il2CppObject* self, Il2CppObject* saberType) {

    OneSaberCheck(self, saberType);

    oneSaber = *il2cpp_utils::GetFieldValue<bool>(self, "_allowOnlyOneSaber");
    
    il2cpp_utils::RunMethod(mainSettingsModel, "Load", true);
}

extern "C" void load() {//Called when installing the hooks

    InitConfig();

    log(INFO, "Installing hooks...");//Logging "Installing hooks..." before the hooks have started to hook
    INSTALL_HOOK_OFFSETLESS(DidActivate, il2cpp_utils::FindMethodUnsafe("", "ControllersTransformSettingsViewController", "DidActivate", 2));//Changes the slider minimum and maximum values
    INSTALL_HOOK_OFFSETLESS(ButtonDidActivate, il2cpp_utils::FindMethodUnsafe("", "SettingsNavigationController", "HandleFinishButton", 1));//Stores the slider value for later use
    INSTALL_HOOK_OFFSETLESS(PlayerController_Update, il2cpp_utils::FindMethodUnsafe("", "PlayerController", "Update", 0));//Changes the saber position and rotation
    INSTALL_HOOK_OFFSETLESS(PlayerSettingsStart, il2cpp_utils::FindMethodUnsafe("", "FormattedFloatListSettingsController", "GetInitValues", 2));
    //Darth Maul Hooks
    INSTALL_HOOK_OFFSETLESS(Refresh, il2cpp_utils::FindMethodUnsafe("", "GameplayModifierToggle", "Start", 0));
    INSTALL_HOOK_OFFSETLESS(SongStart, il2cpp_utils::FindMethodUnsafe("", "StandardLevelScenesTransitionSetupDataSO", "Init", 8));
    INSTALL_HOOK_OFFSETLESS(SongFinish, il2cpp_utils::FindMethodUnsafe("", "StandardLevelScenesTransitionSetupDataSO", "Finish", 1));
    INSTALL_HOOK_OFFSETLESS(HapticFeedbackController_Rumble, il2cpp_utils::FindMethodUnsafe("", "VRPlatformHelper", "TriggerHapticPulse", 2));
    INSTALL_HOOK_OFFSETLESS(ModifierChanged, il2cpp_utils::FindMethodUnsafe("", "GameplayModifiersModelSO", "SetModifierBoolValue", 3));
    INSTALL_HOOK_OFFSETLESS(SettingsLoad, il2cpp_utils::FindMethodUnsafe("", "MainSettingsModelSO", "Load", 1));
    INSTALL_HOOK_OFFSETLESS(Install, il2cpp_utils::FindMethodUnsafe("", "MainSystemInit", "Init", 0));
    INSTALL_HOOK_OFFSETLESS(Triggers, il2cpp_utils::FindMethodUnsafe("", "VRControllersInputManager", "TriggerValue", 1));
    INSTALL_HOOK_OFFSETLESS(ControllerUpdate, il2cpp_utils::FindMethodUnsafe("", "VRController", "Update", 0));
    INSTALL_HOOK_OFFSETLESS(PauseStart, il2cpp_utils::FindMethodUnsafe("", "PauseMenuManager", "Start", 0));
    INSTALL_HOOK_OFFSETLESS(PauseFinish, il2cpp_utils::FindMethodUnsafe("", "PauseMenuManager", "OnDestroy", 0));
    INSTALL_HOOK_OFFSETLESS(SettingsCell, il2cpp_utils::FindMethodUnsafe("", "MainSettingsTableCell", "SelectionDidChange", 1));
    INSTALL_HOOK_OFFSETLESS(OneSaberCheck, il2cpp_utils::FindMethodUnsafe("", "SaberManager", "AllowOnlyOneSaber", 1));
    log(INFO, "Installed all hooks!");//Logging "Installed all hooks!" after all hooks have successfully installed
}
