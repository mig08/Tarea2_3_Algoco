import matplotlib.pyplot as plt
#import tikzplotlib


# Datos de cantidad de letras (x) y tiempo (y)
cantidad_letras_dp = [4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14]
tiempo_dp = [15259, 16697, 18495, 20119, 26385, 21226, 23265, 23720, 27026, 29308, 31102]  # Asumiendo que los valores faltantes son 0

# Crear el gráfico de dispersión (scatter plot)
plt.scatter(cantidad_letras_dp, tiempo_dp, color='b', marker='o')

# Agregar etiquetas y título
plt.xlabel('Cantidad de Letras')
plt.ylabel('Tiempo')
plt.title('Cantidad de Letras vs. Tiempo')
plt.yscale('log')

# Mostrar el gráfico
plt.grid(True, which="both", ls="--")
plt.show()
#tikzplotlib.save('grafico_dp.tikz')



# Datos de cantidad de letras y tiempo en nanosegundos
cantidad_letras = [4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14]
tiempo_ns = [25200, 48624, 198206, 1024360, 5381835, 30039713, 161451058, 865655638, 28526771974, 160535398672, 940537928386]

plt.scatter(cantidad_letras, tiempo_ns, color='blue', marker='*')

plt.xlabel('Cantidad de Letras')
plt.ylabel('Tiempo [ns]')

plt.title('Gráfico de Cantidad de Letras vs Tiempo')

plt.yscale('log')

plt.grid(True, which="both", ls="--")
plt.show()

#tikzplotlib.save('grafico_fb.tikz')



# Datos de cantidad de letras (x) y tiempo (y)
cantidad_letras = [4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14]
tiempo_fuerza_bruta = [627000, 998000, 1001000, 2476000, 9679000, 59028000, 289090000, 1562773000, 50685238000, 286045667000, 952465039304]
tiempo_programacion_dinamica = [15259, 16697, 18495, 20119, 26385, 21226, 23265, 23720, 27026, 29308, 31102]

# Crear el gráfico
plt.figure(figsize=(10, 6))

# Plot Fuerza Bruta (línea azul)
plt.scatter(cantidad_letras, tiempo_fuerza_bruta, color='blue', label='Línea azul: Fuerza Bruta', marker='s')

# Plot Programación Dinámica (línea magenta)
plt.scatter(cantidad_letras, tiempo_programacion_dinamica, color='magenta', label='Línea Magenta: Programación Dinámica', marker='s')

# Configuración del gráfico
plt.xlabel('Número de Letras')
plt.ylabel('Tiempo [ns]')
plt.title('Cantidad de Letras vs Tiempo')
plt.yscale('log')  # Escala logarítmica en el eje Y
plt.grid(True, which="both", linestyle='--', linewidth=0.5)

# Mostrar leyenda
plt.legend()

# Guardar el gráfico como archivo TikZ
#tikzplotlib.save("grafico.tikz")

# Mostrar el gráfico
plt.show()



