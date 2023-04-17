lua << EOF
local dap = require('dap')
require('dap.ext.vscode').load_launchjs(nil, { codelldb = {'c', 'cpp'} })

-- Delete the following configuration to launch json configurations in .vscode/launch.json
dap.configurations.cpp = {
    {
        -- Change it to "cppdbg" if you have vscode-cpptools
        type = "codelldb",
	name = "Select executable",
        request = "launch",

        program = function ()
	    return vim.fn.input('Path to executable: ', vim.fn.getcwd() .. '/build/debug/', 'file')
        end,

        args = function ()
            local argv = {}
            arg = vim.fn.input(string.format("argv: "))
            for a in string.gmatch(arg, "%S+") do
                table.insert(argv, a)
            end
            vim.cmd('echo ""')
            return argv
        end,

        cwd = "${workspaceFolder}/build/debug",

        -- Uncomment if you want to stop at main
        stopAtEntry = true,
        MIMode = "gdb",
        miDebuggerPath = "/usr/bin/gdb",
        setupCommands = {
            {
                text = "-enable-pretty-printing",
                description = "enable pretty printing",
                ignoreFailures = false,
            },
        },
    },

    {
        -- Change it to "cppdbg" if you have vscode-cpptools
        type = "codelldb",
	name = "PAR",
        request = "launch",

        program = function ()
            return 'build/debug/PAR'
        end,

        args = function ()
            local argv = {}
            arg = vim.fn.input(string.format("argv: "))
            for a in string.gmatch(arg, "%S+") do
                table.insert(argv, a)
            end
            vim.cmd('echo ""')
            return argv
        end,

        cwd = "${workspaceFolder}/build/debug",

        -- Uncomment if you want to stop at main
        stopAtEntry = true,
        MIMode = "gdb",
        miDebuggerPath = "/usr/bin/gdb",
        setupCommands = {
            {
                text = "-enable-pretty-printing",
                description = "enable pretty printing",
                ignoreFailures = false,
            },
        },
    }
}
EOF

