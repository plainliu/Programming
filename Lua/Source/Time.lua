--[[
	* 2020.04.06
	* time func
]]

local Time = {}

-- Default Beijing +8:00
Time.timeZone = 8
Time.getTimeZone = function(self)
	return self.timeZone
end
Time.setTimeZone = function(self, timezone)
	assert(type(timezone) == 'number')

	self.timeZone = timezone
end

Time.mktime = function(self, year, mon, day, hour, min, sec)
	mon = mon - 2
	if mon <= 0 then
		mon = mon + 12
		year = year - 1
	end

	Y = math.floor(year / 4) - math.floor(year / 100) + math.floor(year / 400)
	Z = math.floor(367 * mon / 12)
	W = year * 365 + day
	X = Y + Z + W - 719499
	return ((X * 24 + hour - self:getTimeZone()) * 60 + min) * 60 + sec
end

Time.isLeapYear = function(self, year)
	return math.fmod(year, 4) == 0 and (math.fmod(year, 100) ~= 0 or math.fmod(year, 400) == 0)
end
Time.localtime1 = function(self, result, time)
	result.sec = time % 60
	time = math.floor(time / 60)
	result.min = time % 60
	time = math.floor(time / 60) + self:getTimeZone()
	result.hour = time % 24
	local days = math.floor(time / 24)
	return days
end
Time.localtime2 = function(self, result, days)
	-- 1970-01-01 (days=0) was a Thursday (4).
	-- -1 and +1 map Sunday properly onto 7.
	result.wday = (4 + days - 1) % 7 + 1;
end
Time.localtime3 = function(self, result, days)
	-- 1970.01.01 days = 0
	days = days + 1
	local year = 1970
	for i = 1, math.ceil(days / 365) do
		local ldays = 365
		if self:isLeapYear(year) then
			ldays = 366
		end
		if days - ldays > 0 then
			year = year + 1
			days = days - ldays
		else
			result.year = year
			break
		end
	end
	return days
end
Time.localtime4 = function(self, result, yearday)
	assert(yearday > 0 and yearday <= 366, 'Invaild yearday!')

	local monthdays = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
	if self:isLeapYear(result.year) then
		monthdays[2] = 29
	end
	local mon = 1
	for i = 1, 12 do
		if yearday - monthdays[i] > 0 then
			yearday = yearday - monthdays[i]
			mon = mon + 1
		else
			result.mon = mon
			return yearday
		end
	end
end
Time.localtime = function(self, time)
	local date = {}
	local days = self:localtime1(date, time)
	self:localtime2(date, days)
	local yearday = self:localtime3(date, days)
	local monthday = self:localtime4(date, yearday)
	date.day = monthday
	return date
end

return Time