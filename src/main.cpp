#include "../include/main.hpp"

#include <iostream> 
#include <string.h>

Il2CppObject* posXSlider;//The X slider
Il2CppObject* posYSlider;//The Y slider
Il2CppObject* posZSlider;//The Z slider

float xSliderValue;//The X slider value
float ySliderValue;//The Y slider value
float zSliderValue;//The Z slider value

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

    //Setting the properties of X slider
    il2cpp_utils::RunMethod(posXSlider, "set_maxValue", num);//Changing the max value to num
    il2cpp_utils::RunMethod(posXSlider, "set_minValue", num2);//Changing the minumum value to negative of num
    il2cpp_utils::RunMethod(posXSlider, "set_numberOfSteps", numberOfSteps);//Making it so the steps still go by tenths

    il2cpp_utils::GetFieldValue(&posYSlider, self, "_posYSlider");//Finding the position Y slider

    //Setting the properties of Y slider
    il2cpp_utils::RunMethod(posYSlider, "set_maxValue", num);//Changing the max value to num
    il2cpp_utils::RunMethod(posYSlider, "set_minValue", num2);//Changing the minumum value to negative of num
    il2cpp_utils::RunMethod(posYSlider, "set_numberOfSteps", numberOfSteps);//Making it so the steps still go by tenths

    il2cpp_utils::GetFieldValue(&posZSlider, self, "_posZSlider");//Finding the position Z slider

    //Setting the properties of Z slider
    il2cpp_utils::RunMethod(posZSlider, "set_maxValue", num);//Changing the max value to num
    il2cpp_utils::RunMethod(posZSlider, "set_minValue", num2);//Changing the minumum value to negative of num
    il2cpp_utils::RunMethod(posZSlider, "set_numberOfSteps", numberOfSteps);//Making it so the steps still go by tenths

    xSliderValue = charToFloat(readfile("storage/emulated/0/Android/data/com.beatgames.beatsaber/files/MoreOptionsDataX.txt"));
    ySliderValue = charToFloat(readfile("storage/emulated/0/Android/data/com.beatgames.beatsaber/files/MoreOptionsDataY.txt"));
    zSliderValue = charToFloat(readfile("storage/emulated/0/Android/data/com.beatgames.beatsaber/files/MoreOptionsDataZ.txt"));

    il2cpp_utils::RunMethod(posXSlider, "set_value", xSliderValue);//Setting the X slider value to xSliderValue
    il2cpp_utils::RunMethod(posYSlider, "set_value", ySliderValue);//Setting the Y slider value to ySliderValue
    il2cpp_utils::RunMethod(posZSlider, "set_value", zSliderValue);//Setting the Z slider value to zSliderValue
}

MAKE_HOOK_OFFSETLESS(EnteredSettings, void, Il2CppObject* self, bool firstActivation, int activationType) {//Called when entering the settings menu

    il2cpp_utils::RunMethod(posXSlider, "set_value", xSliderValue);//Setting the X slider value to xSliderValue
    il2cpp_utils::RunMethod(posYSlider, "set_value", ySliderValue);//Setting the Y slider value to ySliderValue
    il2cpp_utils::RunMethod(posZSlider, "set_value", zSliderValue);//Setting the Z slider value to zSliderValue

    EnteredSettings(self, firstActivation, activationType);//calling the function after setting the values
}

MAKE_HOOK_OFFSETLESS(EnteredMainMenu, void, Il2CppObject* self, bool firstActivation, int activationType) {//Called when entering the settings menu

    if(firstEnter) {
        il2cpp_utils::RunMethod(posXSlider, "set_value", xSliderValue);//Setting the X slider value to xSliderValue
        il2cpp_utils::RunMethod(posYSlider, "set_value", ySliderValue);//Setting the Y slider value to ySliderValue
        il2cpp_utils::RunMethod(posZSlider, "set_value", zSliderValue);//Setting the Z slider value to zSliderValue
    
        firstEnter = false;
    }

    EnteredMainMenu(self, firstActivation, activationType);//calling the function after setting the values
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

        writefile("storage/emulated/0/Android/data/com.beatgames.beatsaber/files/MoreOptionsDataX.txt", std::to_string(xSliderValue).data());
        writefile("storage/emulated/0/Android/data/com.beatgames.beatsaber/files/MoreOptionsDataY.txt", std::to_string(ySliderValue).data());
        writefile("storage/emulated/0/Android/data/com.beatgames.beatsaber/files/MoreOptionsDataZ.txt", std::to_string(zSliderValue).data());
    }

    ButtonDidActivate(self, finishAction);//Calling the function after having stored the slider values
}

MAKE_HOOK_OFFSETLESS(PlayerController_Update, void, Il2CppObject* self) {
    
    PlayerController_Update(self);//Calling the function before changing values

    log(DEBUG, "%f %f %f", xSliderValue, ySliderValue, zSliderValue);

    Il2CppObject* leftSaber = il2cpp_utils::GetFieldValue(self, "_leftSaber");//Getting the left saber
    Il2CppObject* rightSaber = il2cpp_utils::GetFieldValue(self, "_rightSaber");//Getting the right saber

    if(leftSaber != nullptr && rightSaber != nullptr) {//Checking if the sabers equal something
        
        log(DEBUG, "%f %f %f", xSliderValue, ySliderValue, zSliderValue);
        
        Il2CppObject* leftSaberTransform = nullptr;//Setting the left saber transform to a null pointer value
        Il2CppObject* rightSaberTransform = nullptr;//Setting the right saber transform to a null pointer value

        Il2CppClass* componentsClass = il2cpp_utils::GetClassFromName("", "Saber");//Making a variable that is the saber class
        il2cpp_utils::RunMethod(&leftSaberTransform, leftSaber, il2cpp_functions::class_get_method_from_name(componentsClass, "get_transform", 0));//Getting the left saber transform
        il2cpp_utils::RunMethod(&rightSaberTransform, rightSaber, il2cpp_functions::class_get_method_from_name(componentsClass, "get_transform", 0));//Getting the right saber transform

        if(leftSaberTransform != nullptr && rightSaberTransform != nullptr) {//Checking if the saber transforms equal something

            Il2CppClass* transformClass = il2cpp_utils::GetClassFromName("UnityEngine", "Transform");//Making a variable that is the Transform class from the Unity Engine dll
            const MethodInfo* setRotate = il2cpp_functions::class_get_method_from_name(transformClass, "Rotate", 1);//Making it possible to change the saber rotations
            const MethodInfo* setTranslate = il2cpp_functions::class_get_method_from_name(transformClass, "Translate", 1);//Making it possible to change the saber positions

            log(DEBUG, "%f %f %f", xSliderValue, ySliderValue, zSliderValue);

            il2cpp_utils::RunMethod(leftSaberTransform, setTranslate, Vector3{ (-xSliderValue)/100.0f, ySliderValue/100.0f, zSliderValue/100.0f});//Setting the left saber position to the slider values
            il2cpp_utils::RunMethod(rightSaberTransform, setTranslate, Vector3{ xSliderValue/100.0f, ySliderValue/100.0f, zSliderValue/100.0f});//Setting the right saber position to the slider values
        }
    }
}

MAKE_HOOK_OFFSETLESS(TrailIntensityChange, void, Il2CppObject* self) {

    Il2CppObject* trailIntensitySlider;
    il2cpp_utils::GetFieldValue(&trailIntensitySlider, self, "_saberTrailIntensitySettingsController");

    float max = 10.0f;
    il2cpp_utils::SetFieldValue(trailIntensitySlider, "_max", &max);

    log(INFO, "Trail Intensity has Changed");

    TrailIntensityChange(self);
}

extern "C" void load() {//Called when installing the hooks

    if(!fileexists("storage/emulated/0/Android/data/com.beatgames.beatsaber/files/MoreOptionsDataX.txt")) {
        writefile("storage/emulated/0/Android/data/com.beatgames.beatsaber/files/MoreOptionsDataX.txt", "0");
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
	
    xSliderValue = charToFloat(readfile("storage/emulated/0/Android/data/com.beatgames.beatsaber/files/MoreOptionsDataX.txt"));
    ySliderValue = charToFloat(readfile("storage/emulated/0/Android/data/com.beatgames.beatsaber/files/MoreOptionsDataY.txt"));
    zSliderValue = charToFloat(readfile("storage/emulated/0/Android/data/com.beatgames.beatsaber/files/MoreOptionsDataZ.txt"));
	
    log(INFO, "Installing hooks...");//Logging "Installing hooks..." before the hooks have started to hook
    INSTALL_HOOK_OFFSETLESS(DidActivate, il2cpp_utils::FindMethodUnsafe("", "ControllersTransformSettingsViewController", "DidActivate", 2));//Changes the slider minimum and maximum values
    //INSTALL_HOOK_OFFSETLESS(EnteredSettings, il2cpp_utils::FindMethodUnsafe("", "SettingsNavigationController", "DidActivate", 2));//Changes the slider value to the stored value
    //INSTALL_HOOK_OFFSETLESS(EnteredMainMenu, il2cpp_utils::FindMethodUnsafe("", "MainMenuViewController", "DidActivate", 2));//Changes the saber position and rotation
    INSTALL_HOOK_OFFSETLESS(ButtonDidActivate, il2cpp_utils::FindMethodUnsafe("", "SettingsNavigationController", "HandleFinishButton", 1));//Stores the slider value for later use
    INSTALL_HOOK_OFFSETLESS(PlayerController_Update, il2cpp_utils::FindMethodUnsafe("", "PlayerController", "Update", 0));//Changes the saber position and rotation
    INSTALL_HOOK_OFFSETLESS(TrailIntensityChange, il2cpp_utils::FindMethodUnsafe("", "PlayerSettingsPanelController", "Awake", 0));//Changes the saber position and rotation
    log(INFO, "Installed all hooks!");//Logging "Installed all hooks!" after all hooks have successfully installed
}
