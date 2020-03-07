let testPath = Filename.current_dir_name;
include Rely.Make({
  let config =
    Rely.TestFrameworkConfig.initialize({
      snapshotDir: Filename.concat(testPath, "/__snapshots__"),
      projectDir: Filename.concat(testPath, "../")
    });
});