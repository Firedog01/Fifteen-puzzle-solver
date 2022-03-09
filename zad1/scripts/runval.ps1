# Run a program validating solutions to the 15-puzzle stored in files in the
# current directory against corresponding initial states of the puzzle also
# stored in files in the current directory in a batch mode.
#
# The names of the files storing the initial states of the puzzle should obey
# the following format:
#  size_depth_id.txt
# for example:
#  4x4_01_00001.txt
#
# The names of the files storing the solutions to the puzzle should obey the
# following format:
#  size_depth_id_strategy_param_sol.txt
# for example:
#  4x4_01_00001_bfs_rdul_sol.txt
#
# TODO: Change variable $Progcmd to match the command needed to invoke the
# actual program, using the absolute (or relative) path, for example:
#  $Progcmd = 'java -jar C:\Users\User\15puzzle\bin\puzzleval.jar'

$Progcmd = 'echo program'
$SolFilenameRegex = '^[a-zA-Z0-9]+_[0-9]+_[0-9]+_[a-zA-Z]+_[a-zA-Z]+_sol.txt$'

$NumCorrectSols = 0
$NumIncorrectSols = 0
[System.Collections.ArrayList]$IncorrectSolFilenames = @()
Get-ChildItem -File | Where-Object { $_.Name -match $SolFilenameRegex } | ForEach-Object {
    $SplitFilename = $_.Name.Split('_');
    $InitFilename = $('{0}_{1}_{2}.txt' -f $SplitFilename[0], $SplitFilename[1], $SplitFilename[2])
    Write-Host $('{0}: ' -f $_.Name) -NoNewline
    Invoke-Expression $('{0} {1} {2}' -f $Progcmd, $InitFilename, $_.Name)
    if ($LastExitCode -eq 0) {
        $NumCorrectSols++
    } elseif ($LastExitCode -eq 1) {
        $NumIncorrectSols++;
        [void]$IncorrectSolFilenames.Add($_.Name)
    } else {
        Write-Error 'Fatal error.'
        exit 1
    }
}

Write-Host '----- Summary -----'
Write-Host $('Correct solutions: {0}' -f $NumCorrectSols) -ForegroundColor Green
Write-Host $('Incorrect solutions: {0}' -f $NumIncorrectSols) -ForegroundColor Red
foreach($Filename in $IncorrectSolFilenames) {
    Write-Host $Filename -ForegroundColor Red
}
