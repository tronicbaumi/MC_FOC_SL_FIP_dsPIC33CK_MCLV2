exec('current_cold.sce',-1);
exec('current_warm.sce',-1);

scf(101);

plot(current_cold_var.Data.TimeStamp,current_cold_var.Data.Channel2.Values);
plot(current_warm_var.Data.TimeStamp,current_warm_var.Data.Channel2.Values);
