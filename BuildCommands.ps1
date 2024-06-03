# function definitions, you can copy an paste in the terminal and use them
function play {
    scons platform=windows
    # make sure to have Godot_v4.1.4-stable_win64_console.exe in path or put the absolute path, also change
    Godot_v4.1.4-stable_win64_console.exe --path .\project
}

function editor {
    scons platform=windows
    Godot_v4.1.4-stable_win64_console.exe -e --path .\project
}

function openEditor {
    Godot_v4.1.4-stable_win64_console.exe -e --path .\project
}