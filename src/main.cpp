#include "../include/main.hpp"

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

Il2CppObject* controllerPosition;

bool firstEnter = true;

float charToFloat(const char* charVar) {
    float returned = atof(charVar);
    return returned;
}

MAKE_HOOK_OFFSETLESS(DidActivate, void, Il2CppObject* self, bool firstActivation, int activationType) {//Called when entering the controllers section of the settings menu

    DidActivate(self, firstActivation, activationType);//Calling the function before changing everything so that the changes stay the same

    float num = 50.0f;//This will be the maximum value of the sliders
    float num2 = -num;//This will be the minimum value the sliders (set to negative of num)
	int numberOfSteps = ((num - num2) / 0.1f) + 1;//Finding the number of steps
    
    il2cpp_utils::GetFieldValue(&posXSlider, self, "_posXSlider");//Finding the position X slider
    il2cpp_utils::GetFieldValue(&posYSlider, self, "_posYSlider");//Finding the position Y slider
    il2cpp_utils::GetFieldValue(&posZSlider, self, "_posZSlider");//Finding the position Z slider
    
    il2cpp_utils::GetFieldValue(&rotXSlider, self, "_rotXSlider");//Finding the position X slider
    il2cpp_utils::GetFieldValue(&rotYSlider, self, "_rotYSlider");//Finding the position Y slider
    il2cpp_utils::GetFieldValue(&rotZSlider, self, "_rotZSlider");//Finding the position Z slider

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

    if(noArrows) {
        xSliderValue = charToFloat(readfile("storage/emulated/0/Android/data/com.beatgames.beatsaber/files/MoreOptionsDataXD.txt"));
        ySliderValue = charToFloat(readfile("storage/emulated/0/Android/data/com.beatgames.beatsaber/files/MoreOptionsDataYD.txt"));
        zSliderValue = charToFloat(readfile("storage/emulated/0/Android/data/com.beatgames.beatsaber/files/MoreOptionsDataZD.txt"));

        rotXSliderValue = charToFloat(readfile("storage/emulated/0/Android/data/com.beatgames.beatsaber/files/MoreOptionsDataRotXD.txt"));
        rotYSliderValue = charToFloat(readfile("storage/emulated/0/Android/data/com.beatgames.beatsaber/files/MoreOptionsDataRotYD.txt"));
        rotZSliderValue = charToFloat(readfile("storage/emulated/0/Android/data/com.beatgames.beatsaber/files/MoreOptionsDataRotZD.txt"));
    } else {
        xSliderValue = charToFloat(readfile("storage/emulated/0/Android/data/com.beatgames.beatsaber/files/MoreOptionsDataX.txt"));
        ySliderValue = charToFloat(readfile("storage/emulated/0/Android/data/com.beatgames.beatsaber/files/MoreOptionsDataY.txt"));
        zSliderValue = charToFloat(readfile("storage/emulated/0/Android/data/com.beatgames.beatsaber/files/MoreOptionsDataZ.txt"));

        rotXSliderValue = charToFloat(readfile("storage/emulated/0/Android/data/com.beatgames.beatsaber/files/MoreOptionsDataRotX.txt"));
        rotYSliderValue = charToFloat(readfile("storage/emulated/0/Android/data/com.beatgames.beatsaber/files/MoreOptionsDataRotY.txt"));
        rotZSliderValue = charToFloat(readfile("storage/emulated/0/Android/data/com.beatgames.beatsaber/files/MoreOptionsDataRotZ.txt"));
    }

    il2cpp_utils::RunMethod(posXSlider, "set_value", xSliderValue);//Setting the X slider value to xSliderValue
    il2cpp_utils::RunMethod(posYSlider, "set_value", ySliderValue);//Setting the Y slider value to ySliderValue
    il2cpp_utils::RunMethod(posZSlider, "set_value", zSliderValue);//Setting the Z slider value to zSliderValue

    il2cpp_utils::RunMethod(rotXSlider, "set_value", rotXSliderValue);//Setting the X slider value to xSliderValue
    il2cpp_utils::RunMethod(rotYSlider, "set_value", rotYSliderValue);//Setting the Y slider value to ySliderValue
    il2cpp_utils::RunMethod(rotZSlider, "set_value", rotZSliderValue);//Setting the Z slider value to zSliderValue

}

MAKE_HOOK_OFFSETLESS(ButtonDidActivate, void, Il2CppObject* self, int finishAction) {//Called when pressing any of the settings buttons ("Ok", "Cancel", and "Apply")
    
    if(finishAction == 0) {//Called when the "Ok" setting button is pressed
        log(INFO, "Ok Button Pressed");//Logging when the "Ok" setting button is pressed
    }
    else if(finishAction == 1) {//Called when the "Cancel" setting button is pressed
        log(INFO, "Cancel Button Pressed");//Logging when the "Cancel" setting button is pressed
    }
    else if(finishAction == 2) {//Called when the "Apply" setting button is pressed
        log(INFO, "Apply Button Pressed");//Logging when the "Apply" setting button is pressed
    }

    if(finishAction == 0 || finishAction == 2) {
        il2cpp_utils::RunMethod(&xSliderValue, posXSlider, "get_value");//Getting the value of the X Slider and setting it to xSliderValue
        il2cpp_utils::RunMethod(&ySliderValue, posYSlider, "get_value");//Getting the value of the Y Slider and setting it to ySliderValue
        il2cpp_utils::RunMethod(&zSliderValue, posZSlider, "get_value");//Getting the value of the Z Slider and setting it to zSliderValue

        il2cpp_utils::RunMethod(&rotXSliderValue, rotXSlider, "get_value");//Getting the value of the X Slider and setting it to xSliderValue
        il2cpp_utils::RunMethod(&rotYSliderValue, rotYSlider, "get_value");//Getting the value of the Y Slider and setting it to ySliderValue
        il2cpp_utils::RunMethod(&rotZSliderValue, rotZSlider, "get_value");//Getting the value of the Z Slider and setting it to zSliderValue
        
        if(!noArrows) {
            writefile("storage/emulated/0/Android/data/com.beatgames.beatsaber/files/MoreOptionsDataX.txt", std::to_string(xSliderValue).data());
            writefile("storage/emulated/0/Android/data/com.beatgames.beatsaber/files/MoreOptionsDataY.txt", std::to_string(ySliderValue).data());
            writefile("storage/emulated/0/Android/data/com.beatgames.beatsaber/files/MoreOptionsDataZ.txt", std::to_string(zSliderValue).data());

            writefile("storage/emulated/0/Android/data/com.beatgames.beatsaber/files/MoreOptionsDataRotX.txt", std::to_string(rotXSliderValue).data());
            writefile("storage/emulated/0/Android/data/com.beatgames.beatsaber/files/MoreOptionsDataRotY.txt", std::to_string(rotYSliderValue).data());
            writefile("storage/emulated/0/Android/data/com.beatgames.beatsaber/files/MoreOptionsDataRotZ.txt", std::to_string(rotZSliderValue).data());
        } else {
            writefile("storage/emulated/0/Android/data/com.beatgames.beatsaber/files/MoreOptionsDataXD.txt", std::to_string(xSliderValue).data());
            writefile("storage/emulated/0/Android/data/com.beatgames.beatsaber/files/MoreOptionsDataYD.txt", std::to_string(ySliderValue).data());
            writefile("storage/emulated/0/Android/data/com.beatgames.beatsaber/files/MoreOptionsDataZD.txt", std::to_string(zSliderValue).data());

            writefile("storage/emulated/0/Android/data/com.beatgames.beatsaber/files/MoreOptionsDataRotXD.txt", std::to_string(rotXSliderValue).data());
            writefile("storage/emulated/0/Android/data/com.beatgames.beatsaber/files/MoreOptionsDataRotYD.txt", std::to_string(rotYSliderValue).data());
            writefile("storage/emulated/0/Android/data/com.beatgames.beatsaber/files/MoreOptionsDataRotZD.txt", std::to_string(rotZSliderValue).data());
        }
    }

    il2cpp_utils::RunMethod(posXSlider, "set_value", 0.0f);//Setting the X slider value to xSliderValue
    il2cpp_utils::RunMethod(posYSlider, "set_value", 0.0f);//Setting the Y slider value to ySliderValue
    il2cpp_utils::RunMethod(posZSlider, "set_value", 0.0f);//Setting the Z slider value to zSliderValue

    il2cpp_utils::RunMethod(rotXSlider, "set_value", 0.0f);//Setting the X slider value to xSliderValue
    il2cpp_utils::RunMethod(rotYSlider, "set_value", 0.0f);//Setting the Y slider value to ySliderValue
    il2cpp_utils::RunMethod(rotZSlider, "set_value", 0.0f);//Setting the Z slider value to zSliderValue

    Il2CppClass* Sliders = il2cpp_utils::GetClassFromName("HMUI", "RangeValuesTextSlider");
    il2cpp_utils::RunMethodUnsafe(Sliders, "OnDestroy", 0);

    ButtonDidActivate(self, finishAction);//Calling the function after having stored the slider values
}

MAKE_HOOK_OFFSETLESS(PlayerController_Update, void, Il2CppObject* self) {
    
    PlayerController_Update(self);//Calling the function before changing values

    log(INFO, "Running");

    Il2CppObject* leftSaber = il2cpp_utils::GetFieldValue(self, "_leftSaber");//Getting the left saber
    Il2CppObject* rightSaber = il2cpp_utils::GetFieldValue(self, "_rightSaber");//Getting the right saber

    if(leftSaber != nullptr && rightSaber != nullptr) {//Checking if the sabers equal something
        
        Il2CppObject* leftSaberTransform = nullptr;//Setting the left saber transform to a null pointer value
        Il2CppObject* rightSaberTransform = nullptr;//Setting the right saber transform to a null pointer value

        Il2CppClass* componentsClass = il2cpp_utils::GetClassFromName("", "Saber");//Making a variable that is the saber class
        il2cpp_utils::RunMethod(&leftSaberTransform, leftSaber, il2cpp_functions::class_get_method_from_name(componentsClass, "get_transform", 0));//Getting the left saber transform
        il2cpp_utils::RunMethod(&rightSaberTransform, rightSaber, il2cpp_functions::class_get_method_from_name(componentsClass, "get_transform", 0));//Getting the right saber transform

        if(leftSaberTransform != nullptr && rightSaberTransform != nullptr) {//Checking if the saber transforms equal something
            Il2CppClass* transformClass = il2cpp_utils::GetClassFromName("UnityEngine", "Transform");
            const MethodInfo* getMethod = il2cpp_functions::class_get_method_from_name(transformClass, "get_localPosition", 0);
            const MethodInfo* setMethod = il2cpp_functions::class_get_method_from_name(transformClass, "set_localPosition", 1);
            const MethodInfo* setRotate = il2cpp_functions::class_get_method_from_name(transformClass, "Rotate", 1);
            const MethodInfo* setTranslate = il2cpp_functions::class_get_method_from_name(transformClass, "Translate", 1);
            const MethodInfo* getLocalRotation = il2cpp_functions::class_get_method_from_name(transformClass, "get_localRotation", 0);
            const MethodInfo* setLocalRotation = il2cpp_functions::class_get_method_from_name(transformClass, "set_localRotation", 1);

            Vector3 rightSaberLocalPosition;
            Vector3 leftSaberLocalPosition;
            il2cpp_utils::RunMethod(&rightSaberLocalPosition, rightSaberTransform, getMethod);
            il2cpp_utils::RunMethod(&leftSaberLocalPosition, leftSaberTransform, getMethod);
            Quaternion rightSaberLocalRotation;
            Quaternion leftSaberLocalRotation;
            il2cpp_utils::RunMethod(&leftSaberLocalRotation, leftSaberTransform, getLocalRotation);
            il2cpp_utils::RunMethod(&rightSaberLocalRotation, rightSaberTransform, getLocalRotation);

            if(noArrows) {
                if(!leftHand) {
                    il2cpp_utils::RunMethod(rightSaberTransform, setTranslate, Vector3{0, 0, -0.27f});
                    il2cpp_utils::RunMethod(rightSaberTransform, setRotate, Vector3{0, 180, 0});
                    il2cpp_utils::RunMethod(leftSaberTransform, setMethod, rightSaberLocalPosition);
                    il2cpp_utils::RunMethod(leftSaberTransform, setLocalRotation, rightSaberLocalRotation);
                    il2cpp_utils::RunMethod(leftSaberTransform, setTranslate, Vector3{0, 0, 0.07f});
                } else {
                    il2cpp_utils::RunMethod(leftSaberTransform, setTranslate, Vector3{0, 0, -0.27f});
                    il2cpp_utils::RunMethod(leftSaberTransform, setRotate, Vector3{0, 180, 0});
                    il2cpp_utils::RunMethod(rightSaberTransform, setMethod, leftSaberLocalPosition);
                    il2cpp_utils::RunMethod(rightSaberTransform, setLocalRotation, leftSaberLocalRotation);
                    il2cpp_utils::RunMethod(rightSaberTransform, setTranslate, Vector3{0, 0, 0.07f});
                }
            } else {
                il2cpp_utils::RunMethod(leftSaberTransform, setTranslate, Vector3{(-xSliderValue)/100.0f, ySliderValue/100.0f, zSliderValue/100.0f});//Setting the left saber position to the slider values
                il2cpp_utils::RunMethod(rightSaberTransform, setTranslate, Vector3{xSliderValue/100.0f, ySliderValue/100.0f, zSliderValue/100.0f});//Setting the right saber position to the slider values
            }
        }
    }
}

MAKE_HOOK_OFFSETLESS(HapticFeedbackController_Rumble, void, Il2CppObject* self, int node, float duration, float impulseStrength, float intervalDuration) {
    if(noArrows) {
        if(!leftHand) {
            node = 5;
        } else {
            node = 4;
        }
    }
    HapticFeedbackController_Rumble(self, node, duration, impulseStrength, intervalDuration);
}

MAKE_HOOK_OFFSETLESS(TrailIntensityChange, void, Il2CppObject* self, Il2CppObject* settingsController, float value) {
    TrailIntensityChange(self, settingsController, value);

    float max = 10.0f;
    float values;
    il2cpp_utils::RunMethod(settingsController, "set_max", max);
    values = max;

    log(INFO, "%f", values);

}

MAKE_HOOK_OFFSETLESS(Refresh, void, Il2CppObject* self) {
    Refresh(self);
    Il2CppObject* GetGameObject;
    std::string NoArrow = "NoArrows";
    std::string GameObjectString;
    Il2CppString* GameObjectName;
    Il2CppObject* GMT_nameText;
    Il2CppString* textToSet;
 
    if(!il2cpp_utils::RunMethod(&GetGameObject, self, "get_gameObject")){
        log(ERROR, "Failed to get gameObject for GameplayModifierToggle_Start");
    }
 
    if (GetGameObject != nullptr) {
        if(!il2cpp_utils::RunMethod(&GameObjectName, il2cpp_utils::GetClassFromName("UnityEngine", "Object"), "GetName", GetGameObject)){
            log(ERROR, "Failed to get name!");
        }
    }
    if(GameObjectName != nullptr){
        GameObjectString = to_utf8(csstrtostr(GameObjectName));
 
        if(GameObjectString == NoArrow){
            textToSet = il2cpp_utils::createcsstr("<size=90%>No Arrows/Darth Maul Mode</size>\n<color=#ffffff88><size=80%>-0.30</size></color>");
            GMT_nameText = il2cpp_utils::GetFieldValue(self, "_nameText");
            if(!il2cpp_utils::RunMethod(GMT_nameText, "set_text", textToSet)){
                log(ERROR, "Failed to set text");
            }
        }
    }
}

MAKE_HOOK_OFFSETLESS(SongStart, void, Il2CppObject* self, Il2CppObject* difficultyBeatmap, Il2CppObject* overrideEnvironmentSettings, Il2CppObject* overrideColorScheme, Il2CppObject* gameplayModifiers, Il2CppObject* playerSpecificSettings, Il2CppObject* practiceSettings, Il2CppString* backButtonText, bool useTestNoteCutSoundEffects) {

    il2cpp_utils::RunMethod(&leftHand, playerSpecificSettings, "get_leftHanded");
    
    SongStart(self, difficultyBeatmap, overrideEnvironmentSettings, overrideColorScheme, gameplayModifiers, playerSpecificSettings, practiceSettings, backButtonText, useTestNoteCutSoundEffects);
}

MAKE_HOOK_OFFSETLESS(ModifierChanged, void, Il2CppObject* self, Il2CppObject* gameplayModifiers, Il2CppObject* gameplayModifierParams, bool value) {
    ModifierChanged(self, gameplayModifiers, gameplayModifierParams, value);
    
    il2cpp_utils::RunMethod(&noArrows, gameplayModifiers, "get_noArrows");

    if(noArrows) {
        xSliderValue = charToFloat(readfile("storage/emulated/0/Android/data/com.beatgames.beatsaber/files/MoreOptionsDataXD.txt"));
        ySliderValue = charToFloat(readfile("storage/emulated/0/Android/data/com.beatgames.beatsaber/files/MoreOptionsDataYD.txt"));
        zSliderValue = charToFloat(readfile("storage/emulated/0/Android/data/com.beatgames.beatsaber/files/MoreOptionsDataZD.txt"));

        rotXSliderValue = charToFloat(readfile("storage/emulated/0/Android/data/com.beatgames.beatsaber/files/MoreOptionsDataRotXD.txt"));
        rotYSliderValue = charToFloat(readfile("storage/emulated/0/Android/data/com.beatgames.beatsaber/files/MoreOptionsDataRotYD.txt"));
        rotZSliderValue = charToFloat(readfile("storage/emulated/0/Android/data/com.beatgames.beatsaber/files/MoreOptionsDataRotZD.txt"));
    } else {
        xSliderValue = charToFloat(readfile("storage/emulated/0/Android/data/com.beatgames.beatsaber/files/MoreOptionsDataX.txt"));
        ySliderValue = charToFloat(readfile("storage/emulated/0/Android/data/com.beatgames.beatsaber/files/MoreOptionsDataY.txt"));
        zSliderValue = charToFloat(readfile("storage/emulated/0/Android/data/com.beatgames.beatsaber/files/MoreOptionsDataZ.txt"));

        rotXSliderValue = charToFloat(readfile("storage/emulated/0/Android/data/com.beatgames.beatsaber/files/MoreOptionsDataRotX.txt"));
        rotYSliderValue = charToFloat(readfile("storage/emulated/0/Android/data/com.beatgames.beatsaber/files/MoreOptionsDataRotY.txt"));
        rotZSliderValue = charToFloat(readfile("storage/emulated/0/Android/data/com.beatgames.beatsaber/files/MoreOptionsDataRotZ.txt"));
    }
}

MAKE_HOOK_OFFSETLESS(SettingsLoad, void, Il2CppObject* self, bool forced) {

    SettingsLoad(self, forced);

    log(INFO, "Settings have loaded");
    float posOffsetLimit;
    il2cpp_utils::GetFieldValue(&controllerPosition, self, "controllerPosition");
    Vector3 value;
    il2cpp_utils::GetFieldValue(&value, controllerPosition, "value");
    log(DEBUG, "%f", value.x);
}

extern "C" void load() {//Called when installing the hooks
    
    if(!fileexists("storage/emulated/0/Android/data/com.beatgames.beatsaber/files/MoreOptionsDataX.txt")) {
        writefile("storage/emulated/0/Android/data/com.beatgames.beatsaber/files/MoreOptionsDataX.txt", "0.0");
    }
    if(!fileexists("storage/emulated/0/Android/data/com.beatgames.beatsaber/files/MoreOptionsDataY.txt")) {
        writefile("storage/emulated/0/Android/data/com.beatgames.beatsaber/files/MoreOptionsDataY.txt", "0.0");
    }
    if(!fileexists("storage/emulated/0/Android/data/com.beatgames.beatsaber/files/MoreOptionsDataZ.txt")) {
        writefile("storage/emulated/0/Android/data/com.beatgames.beatsaber/files/MoreOptionsDataZ.txt", "0.0");
    }
    if(!fileexists("storage/emulated/0/Android/data/com.beatgames.beatsaber/files/MoreOptionsDataRotX.txt")) {
        writefile("storage/emulated/0/Android/data/com.beatgames.beatsaber/files/MoreOptionsDataRotX.txt", "0.0");
    }
    if(!fileexists("storage/emulated/0/Android/data/com.beatgames.beatsaber/files/MoreOptionsDataRotY.txt")) {
        writefile("storage/emulated/0/Android/data/com.beatgames.beatsaber/files/MoreOptionsDataRotY.txt", "0.0");
    }
    if(!fileexists("storage/emulated/0/Android/data/com.beatgames.beatsaber/files/MoreOptionsDataRotZ.txt")) {
        writefile("storage/emulated/0/Android/data/com.beatgames.beatsaber/files/MoreOptionsDataRotZ.txt", "0.0");
    }
    if(!fileexists("storage/emulated/0/Android/data/com.beatgames.beatsaber/files/MoreOptionsDataXD.txt")) {
        writefile("storage/emulated/0/Android/data/com.beatgames.beatsaber/files/MoreOptionsDataXD.txt", "0.0");
    }
    if(!fileexists("storage/emulated/0/Android/data/com.beatgames.beatsaber/files/MoreOptionsDataYD.txt")) {
        writefile("storage/emulated/0/Android/data/com.beatgames.beatsaber/files/MoreOptionsDataYD.txt", "0.0");
    }
    if(!fileexists("storage/emulated/0/Android/data/com.beatgames.beatsaber/files/MoreOptionsDataZD.txt")) {
        writefile("storage/emulated/0/Android/data/com.beatgames.beatsaber/files/MoreOptionsDataZD.txt", "0.0");
    }
    if(!fileexists("storage/emulated/0/Android/data/com.beatgames.beatsaber/files/MoreOptionsDataRotXD.txt")) {
        writefile("storage/emulated/0/Android/data/com.beatgames.beatsaber/files/MoreOptionsDataRotXD.txt", "0.0");
    }
    if(!fileexists("storage/emulated/0/Android/data/com.beatgames.beatsaber/files/MoreOptionsDataRotYD.txt")) {
        writefile("storage/emulated/0/Android/data/com.beatgames.beatsaber/files/MoreOptionsDataRotYD.txt", "0.0");
    }
    if(!fileexists("storage/emulated/0/Android/data/com.beatgames.beatsaber/files/MoreOptionsDataRotZD.txt")) {
        writefile("storage/emulated/0/Android/data/com.beatgames.beatsaber/files/MoreOptionsDataRotZD.txt", "0.0");
    }
    
    xSliderValue = charToFloat(readfile("storage/emulated/0/Android/data/com.beatgames.beatsaber/files/MoreOptionsDataX.txt"));
    ySliderValue = charToFloat(readfile("storage/emulated/0/Android/data/com.beatgames.beatsaber/files/MoreOptionsDataY.txt"));
    zSliderValue = charToFloat(readfile("storage/emulated/0/Android/data/com.beatgames.beatsaber/files/MoreOptionsDataZ.txt"));
    
    rotXSliderValue = charToFloat(readfile("storage/emulated/0/Android/data/com.beatgames.beatsaber/files/MoreOptionsDataRotX.txt"));
    rotYSliderValue = charToFloat(readfile("storage/emulated/0/Android/data/com.beatgames.beatsaber/files/MoreOptionsDataRotY.txt"));
    rotZSliderValue = charToFloat(readfile("storage/emulated/0/Android/data/com.beatgames.beatsaber/files/MoreOptionsDataRotZ.txt"));

    log(INFO, "Installing hooks...");//Logging "Installing hooks..." before the hooks have started to hook
    INSTALL_HOOK_OFFSETLESS(DidActivate, il2cpp_utils::FindMethodUnsafe("", "ControllersTransformSettingsViewController", "DidActivate", 2));//Changes the slider minimum and maximum values
    INSTALL_HOOK_OFFSETLESS(ButtonDidActivate, il2cpp_utils::FindMethodUnsafe("", "SettingsNavigationController", "HandleFinishButton", 1));//Stores the slider value for later use
    INSTALL_HOOK_OFFSETLESS(PlayerController_Update, il2cpp_utils::FindMethodUnsafe("", "PlayerController", "Update", 0));//Changes the saber position and rotation
    INSTALL_HOOK_OFFSETLESS(TrailIntensityChange, il2cpp_utils::FindMethodUnsafe("", "PlayerSettingsPanelController", "HandleSaberTrailIntensitySettingsControllerValueDidChange", 2));
    //Darth Maul Hooks
    INSTALL_HOOK_OFFSETLESS(Refresh, il2cpp_utils::FindMethodUnsafe("", "GameplayModifierToggle", "Start", 0));
    INSTALL_HOOK_OFFSETLESS(SongStart, il2cpp_utils::FindMethodUnsafe("", "StandardLevelScenesTransitionSetupDataSO", "Init", 8));
    INSTALL_HOOK_OFFSETLESS(HapticFeedbackController_Rumble, il2cpp_utils::FindMethodUnsafe("", "HapticFeedbackController", "Rumble", 4));
    INSTALL_HOOK_OFFSETLESS(ModifierChanged, il2cpp_utils::FindMethodUnsafe("", "GameplayModifiersModelSO", "SetModifierBoolValue", 3));
    INSTALL_HOOK_OFFSETLESS(SettingsLoad, il2cpp_utils::FindMethodUnsafe("", "MainSettingsModelSO", "Load", 1));
    log(INFO, "Installed all hooks!");//Logging "Installed all hooks!" after all hooks have successfully installed
}
