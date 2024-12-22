import os
import pandas as pd
import matplotlib.pyplot as plt
from datetime import datetime
from matplotlib.backends.backend_pdf import PdfPages

# Load data from CSV
filename = "data/perfume_sensor_readings_2024-12-22_22-23-58.csv"  # Adjust the file path if necessary
df = pd.read_csv(filename)

# Parse the 'DateTime' column to datetime
df['DateTime'] = pd.to_datetime(df['DateTime'], format='%Y-%m-%d %H:%M:%S')

# Calculate statistics for numerical columns
stats = {}
for col in df.columns:
    if col != 'DateTime' and df[col].dtype in ['float64', 'int64']:  # Skip non-numerical columns
        col_mean = df[col].mean()
        col_median = df[col].median()
        col_mode = df[col].mode().iloc[0] if not df[col].mode().empty else None
        col_std = df[col].std()
        col_cv = (col_std / col_mean * 100) if col_mean != 0 else 0
        stats[col] = {
            'Mean': col_mean,
            'Median': col_median,
            'Mode': col_mode,
            'Std Dev': col_std,
            'CV%': col_cv
        }

# Convert stats to a DataFrame for better formatting
stats_df = pd.DataFrame(stats).T
stats_df.reset_index(inplace=True)
stats_df.columns = ['Column', 'Mean', 'Median', 'Mode', 'Std Dev', 'CV%']

# Calculate total duration
start_time = df['DateTime'].iloc[0]
end_time = df['DateTime'].iloc[-1]
duration = end_time - start_time

# Format the duration into hours, minutes, and seconds
duration_str = str(duration)

# Generate Plots Dynamically
columns_to_plot = [
    'Humidity(%)', 'Temperature(°C)', 'MQ5_LPG', 'MQ8_H2',
    'MQ7_CO', 'MQ135_Alcohol', 'MQ135_CO2', 'MQ135_Toluen',
    'MQ135_NH4', 'MQ135_Aceton'
]

# Dynamically calculate subplot grid size
num_plots = len(columns_to_plot)
cols = 2
rows = (num_plots + cols - 1) // cols  # Ceiling division

fig, axs = plt.subplots(rows, cols, figsize=(16, 4 * rows))

# Flatten axs for easy indexing if rows > 1
if rows > 1:
    axs = axs.flatten()

# Create a plot for each column
for i, col in enumerate(columns_to_plot):
    axs[i].plot(df['DateTime'], df[col], marker='o', label=col)
    axs[i].set_title(f'{col} vs Time (Duration: {duration_str})')
    axs[i].set_xlabel('Time')
    axs[i].set_ylabel(col)
    axs[i].legend()
    axs[i].grid(True)
    axs[i].tick_params(axis='x', rotation=45)

# Hide any unused subplots
for j in range(num_plots, len(axs)):
    axs[j].axis('off')

plt.tight_layout()

# Save plots and stats to a PDF
base = os.path.basename(filename).split(".csv")[0]
pdf_filename = f"reports/report_{base}.pdf"

with PdfPages(pdf_filename) as pdf:
    # Add a new page with the stats table
    fig2, ax = plt.subplots(figsize=(12, 8))
    ax.axis('tight')
    ax.axis('off')
    table = ax.table(cellText=stats_df.values, colLabels=stats_df.columns, loc='center', cellLoc='center')
    table.auto_set_font_size(False)
    table.set_fontsize(10)
    table.auto_set_column_width(col=list(range(len(stats_df.columns))))
    pdf.savefig(fig2)
    plt.close(fig2)
    
    # Save the plot figure
    pdf.savefig(fig)
    plt.close(fig)

print(f"[INFO] Report saved as {pdf_filename}")
