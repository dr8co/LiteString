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

// Run after the installation has completed
procedure DeinitializeSetup();
begin
  AppPath := ExpandConstant('{app}');
  ReplacePlaceholderInPkgConfig;
end;
