Speed = 30
Duration = 1.5

CurrentTime = 0

function GetSpeed()
	return Speed
end

function Update(DeltaTime)
	CurrentTime = CurrentTime + DeltaTime
	FCT:UpdatePosition(DeltaTime)

	if (CurrentTime >= Duration) then
		FCT:Hide()
	end
end
