Chopper = {
    name = "chooper",
    assetId = "chopper",
    layer = 3,
    components = {
        transform = {
            velocity = {x = 0, y = 0},
            width = 32,
            height= 32,
            scale = 2,
            rotate = 0
        },
        
        collider = { 
            tag = "PLAYER", 
            boundingAssetId = "boundingBox", 
            x = 240,
            y = 106,
            w = 64,
            h = 64
        },
        sprite = {
            assetId = "chopper",
            animated = true,
            numFrames = 2,
            animationSpeed = 90,
            hasDirections = true,
            isFixed = false
        },
        
    }
}

Enemy = {
    prototype = "chopper",
    components = {
        transform = {
            position = {x = 600, y = 400}
        },
        ai = {
            brain = "Assets/Scripts/GOAP1_passive.lua"
        }
    }
}

Player = {
    prototype = "chopper",

    components = {
        transform = {
            position = {x = 240, y = 106},
        },
        camera = {},
        cameraShake = {
            algorithm = 2,
            duration = 15
        },
        input = {
            keyboard = {
                up = "up",
                down = "down",
                left = "left",
                right = "right",
                shoot = "space"
            }
        }
    }
}