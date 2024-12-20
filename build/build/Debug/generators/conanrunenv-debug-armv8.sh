script_folder="/Users/guillaume/Epitech/teck3/cvector/build/build/Debug/generators"
echo "echo Restoring environment" > "$script_folder/deactivate_conanrunenv-debug-armv8.sh"
for v in 
do
    is_defined="true"
    value=$(printenv $v) || is_defined="" || true
    if [ -n "$value" ] || [ -n "$is_defined" ]
    then
        echo export "$v='$value'" >> "$script_folder/deactivate_conanrunenv-debug-armv8.sh"
    else
        echo unset $v >> "$script_folder/deactivate_conanrunenv-debug-armv8.sh"
    fi
done
