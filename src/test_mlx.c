#include <mlx.h>
#include <stdio.h>

int	main(void)
{
	void	*mlx;
	void	*win;

	printf("Iniciando prueba de MLX...\n");
	mlx = mlx_init();
	if (!mlx)
	{
		printf("Error: No se pudo inicializar MLX\n");
		return (1);
	}
	printf("MLX inicializado correctamente\n");

	win = mlx_new_window(mlx, 500, 500, "Test MLX");
	if (!win)
	{
		printf("Error: No se pudo crear la ventana\n");
		return (1);
	}
	printf("Ventana creada correctamente\n");

	mlx_loop(mlx);
	return (0);
} 