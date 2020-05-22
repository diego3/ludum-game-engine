
speed = 30
x = x + speed

-- print("[LUA]", x, speed)
function Initialize()
	-- transform = entity:GetComponent("transform")
	-- transform.x
	-- transform.y

end

function Update(deltaTime) 
	if x > 1000 then
		x = 0
	end 
end

function Render()

end

--[[
https://p5js.org/examples/math-linear-interpolation.html

function Lerp(start, stop, amt) {
  return amt * (stop - start) + start;
};

]]