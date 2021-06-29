--[[
	* 2020.04.06
	* supply basic func for unittest
]]

-- Basic test block
local TestClass = {}
TestClass.new = function(self)
	local o = {}
	o.passCount = 0
	o.failCount = 0

	setmetatable(o, {__index = TestClass})
	return o
end
TestClass.addPassCount = function(self)
	self.passCount = self.passCount + 1
end
TestClass.addFailCount = function(self)
	self.failCount = self.failCount + 1
end
TestClass.getTestCount = function(self)
	return self.passCount + self.failCount
end

local Test = {}
Test.testData = {}

Test.EXPECT_TRUE = function(self, v)
	assert(self.curTestData, 'Use EXPECT_TRUE in UT func!')

	if v then
		self.curTestData:addPassCount()
	else
		self.curTestData:addFailCount()
	end
end
Test.EXPECT_FALSE = function(self, v)
	assert(self.curTestData, 'Use EXPECT_FALSE in UT func!')

	if not v then
		self.curTestData:addPassCount()
	else
		self.curTestData:addFailCount()
	end
end
Test.setTestObject = function(self, data)
	self.curTestData = data
end
Test.resetTestObject = function(self)
	self.curTestData = nil
end
Test.UT = function(self, casename, testname, func)
	if not self.testData[casename] then
		self.testData[casename] = {}
	end
	if not self.testData[casename][testname] then
		self.testData[casename][testname] = TestClass.new()
	end

	self:setTestObject(self.testData[casename][testname])
	func(casename, testname)
	self:resetTestObject()
end

Test.report = function(self)
	local reslut = ''
	local casecount = 0
	local passcount = 0
	print('[+]AllTest', passcount == casecount)
	for casename, testcases in pairs(self.testData) do
		casecount = casecount + 1
		print('[++]TestCase', casename)
		local pass = true
		for testname, test in pairs(testcases) do
			if test.failCount > 0 then
				pass = false
			end
			print('[+++]\tTest', testname)
			print('[---]\tTest', test.failCount == 0, test.failCount .. '/' .. test:getTestCount())
		end
		if pass then
			passcount = passcount + 1
		end
		print('[--]TestCase', pass)
	end
	print('[-]AllTest', passcount == casecount)
end
return Test
