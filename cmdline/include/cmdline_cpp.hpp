#pragma once
namespace cmdline {
	class CmdLine
	{
	public:
		CmdLine();
		~CmdLine();
	private:
		class CmdLineImpl;
		CmdLineImpl* impl_;
	};
}
