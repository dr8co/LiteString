var
  AppPath: string;

procedure ReplacePlaceholderInPkgConfig;
var
  PkgConfigFile: TStringList;
  Index: Integer;
  ModifiedAppPath: string;
begin
  // Read the contents of the liblite-string.pc file
  PkgConfigFile := TStringList.Create;
  try
    PkgConfigFile.LoadFromFile(ExpandConstant('{app}\lib\pkgconfig\liblite-string.pc'));

    // Modify the installation prefix to match the chosen installation destination
    if PkgConfigFile.Count > 0 then
    begin
       // Replace backslashes with forward slashes
       ModifiedAppPath := '';
       for Index := 1 to Length(AppPath) do
       begin
         if AppPath[Index] = '\' then
           ModifiedAppPath := ModifiedAppPath + '/'
         else
           ModifiedAppPath := ModifiedAppPath + AppPath[Index];
       end;
       // Update the prefix
      PkgConfigFile[0] := 'prefix = "' + ModifiedAppPath + '"';
    end;

    // Write the modified contents back to the file
    PkgConfigFile.SaveToFile(ExpandConstant('{app}\lib\pkgconfig\liblite-string.pc'));
  finally
    PkgConfigFile.Free;
  end;
end;

procedure CurStepChanged(CurStep: TSetupStep);
begin
  // Check if the installation is transitioning from ssPostInstall to ssDone
  if (CurStep = ssDone) and (WizardForm.CurPageID = wpFinished) then
  begin
    // Save the installation path
    AppPath := ExpandConstant('{app}');
    // Perform actions after installation
    ReplacePlaceholderInPkgConfig;
  end;
end;
