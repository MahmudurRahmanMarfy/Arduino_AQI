import pandas as pd
import plotly.graph_objects as go
from plotly.subplots import make_subplots

# Load data from CSV
filename = "data/alltest_sensor_readings_2024-12-22_23-10-28.csv"  # Adjust the file path if necessary
df = pd.read_csv(filename)

# Parse the 'DateTime' column to datetime
df['DateTime'] = pd.to_datetime(df['DateTime'], format='%Y-%m-%d %H:%M:%S')

# Calculate total duration
start_time = df['DateTime'].iloc[0]
end_time = df['DateTime'].iloc[-1]
duration = end_time - start_time
duration_str = str(duration)

# Columns to plot
columns_to_plot = [
    'Humidity(%)', 'Temperature(°C)', 'MQ5_LPG', 'MQ8_H2',
    'MQ7_CO', 'MQ135_Alcohol', 'MQ135_CO2', 'MQ135_Toluen',
    'MQ135_NH4', 'MQ135_Aceton'
]

# Define consistent color palette
colors = [
    '#1f77b4', '#ff7f0e', '#2ca02c', '#d62728',
    '#9467bd', '#8c564b', '#e377c2', '#7f7f7f',
    '#bcbd22', '#17becf'
]
color_map = dict(zip(columns_to_plot, colors))

# Create subplots for combined plots
fig = make_subplots(
    rows=2, cols=1,
    subplot_titles=["All Sensor Data", "All Differentiations"]
)

# Add traces for all columns to the first subplot
for col in columns_to_plot:
    fig.add_trace(
        go.Scatter(
            x=df['DateTime'],
            y=df[col] if col != "MQ135_CO2" else df[col] - 400,
            mode='lines',
            name=col,
            legendgroup=col,  # Group legend by column
            line=dict(color=color_map[col])
        ),
        row=1, col=1
    )

# Add traces for all Differentiations to the second subplot
for col in columns_to_plot:
    fig.add_trace(
        go.Scatter(
            x=df['DateTime'],
            y=df[col].diff(),
            mode='lines',
            name=col,
            legendgroup=col,  # Group legend by column
            showlegend=False,  # Hide duplicate legend entries
            line=dict(color=color_map[col])  # Use dashed lines for differentiations
        ),
        row=2, col=1
    )

# Update layout
fig.update_layout(
    title=f"{filename} (Duration: {duration_str})",
    showlegend=True,
)

# Format x-axis for time display
fig.update_xaxes(
    tickformat='%H:%M:%S',  # Show only time
    tickangle=45  # Rotate ticks
)

# Update y-axis labels
fig.update_yaxes(title_text="Sensor Values", row=1, col=1)
fig.update_yaxes(title_text="Differentiations", row=2, col=1)

# Show figure
fig.show()


# Save plots and stats to a PDF
# base = os.path.basename(filename).split(".csv")[0]
# pdf_filename = f"reports/report_{base}.pdf"

# with PdfPages(pdf_filename) as pdf:
#     # Add a new page with the stats table
#     fig2, ax = plt.subplots(figsize=(12, 8))
#     ax.axis('tight')
#     ax.axis('off')
#     table = ax.table(cellText=stats_df.values, colLabels=stats_df.columns, loc='center', cellLoc='center')
#     table.auto_set_font_size(False)
#     table.set_fontsize(10)
#     table.auto_set_column_width(col=list(range(len(stats_df.columns))))
#     pdf.savefig(fig2)
#     plt.close(fig2)
    
#     # Save the plot figure
#     pdf.savefig(fig)
#     plt.close(fig)

# print(f"[INFO] Report saved as {pdf_filename}")
