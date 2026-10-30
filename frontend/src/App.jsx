import { useState, useEffect } from 'react';
import axios from 'axios';
import { LineChart, Line, XAxis, YAxis, CartesianGrid, Tooltip, Legend, ResponsiveContainer } from 'recharts';

export default function App() {
  const [telemetry, setTelemetry] = useState([]);
  
  // --- NEW 1: State for Historical Data (Placed right under your existing state) ---
  const [history, setHistory] = useState([]);

  useEffect(() => {
    const fetchData = async () => {
      try {
        const response = await axios.get('http://127.0.0.1:8000/api/telemetry/live/');
        // Reverse the array so the graph plots left-to-right (oldest to newest)
        setTelemetry(response.data.reverse());
      } catch (error) {
        console.error("Error fetching data:", error);
      }
    };
    
    fetchData();
    const interval = setInterval(fetchData, 1000);
    return () => clearInterval(interval);
  }, []);

  // --- NEW 2: Fetch the History on Load (Placed as a separate useEffect) ---
  useEffect(() => {
    axios.get('http://127.0.0.1:8000/api/telemetry/history/')
      .then(response => {
        setHistory(response.data);
      })
      .catch(error => console.error("Error fetching history:", error));
  }, []);
  const downloadCSV = () => {
    if (history.length === 0) return;
    
    // Define the CSV headers
const headers = ['Timestamp,Status,X_Axis,Y_Axis,Z_Axis,Dominant_Freq,Peak_Amp,Temperature,Current'];    
    // Map the historical data into comma-separated rows
    const rows = history.map(log => 
      `${log.timestamp},${log.machine_status},${log.x_axis},${log.y_axis},${log.z_axis},${log.dominant_freq},${log.peak_amplitude},${log.temperature},${log.current}`    );
    
    // Combine headers and rows
    const csvContent = headers.concat(rows).join('\n');
    
    // Create a downloadable file object in the browser
    const blob = new Blob([csvContent], { type: 'text/csv;charset=utf-8;' });
    const url = URL.createObjectURL(blob);
    
    // Trigger the download
    const link = document.createElement('a');
    link.setAttribute('href', url);
    link.setAttribute('download', 'machine_degradation_report.csv');
    document.body.appendChild(link);
    link.click();
    document.body.removeChild(link);
  };

  return (
    <div style={{ padding: '20px', fontFamily: 'sans-serif', maxWidth: '1000px', margin: '0 auto' }}>
      <h2>Live Machine Diagnostics</h2>
      
      {/* Existing Live Chart */}
      <div style={{ height: '400px', marginBottom: '40px', backgroundColor: '#f9f9f9', padding: '20px', borderRadius: '8px' }}>
        <ResponsiveContainer width="100%" height="100%">
          <LineChart data={telemetry}>
            <CartesianGrid strokeDasharray="3 3" />
            <XAxis dataKey="timestamp" tick={false} />
            <YAxis domain={[-15, 15]} />
            <Tooltip />
            <Legend />
            <Line type="monotone" dataKey="x_axis" stroke="#8884d8" dot={false} isAnimationActive={false} />
            <Line type="monotone" dataKey="y_axis" stroke="#82ca9d" dot={false} isAnimationActive={false} />
            <Line type="monotone" dataKey="z_axis" stroke="#ffc658" dot={false} isAnimationActive={false} />
          </LineChart>
        </ResponsiveContainer>
      </div>

      {/* --- NEW 3: Historical Chart --- */}
      <div style={{ height: '400px', marginBottom: '40px', backgroundColor: '#e3f2fd', padding: '20px', borderRadius: '8px' }}>
        
        {/* --- UPDATED HEADER WITH BUTTON --- */}
        <div style={{ display: 'flex', justifyContent: 'space-between', alignItems: 'center', marginBottom: '10px' }}>
            <h3 style={{ margin: 0 }}>Historical Frequency Trend (Last 100 Readings)</h3>
            <button 
              onClick={downloadCSV}
              style={{ padding: '8px 16px', backgroundColor: '#1976d2', color: 'white', border: 'none', borderRadius: '4px', cursor: 'pointer', fontWeight: 'bold' }}
            >
              ⬇ Download CSV Report
            </button>
        </div>
        {/* -------------------------------- */}

        <ResponsiveContainer width="100%" height="100%">
          <LineChart data={history}>
            <CartesianGrid strokeDasharray="3 3" />
            <XAxis dataKey="timestamp" tick={false} />
            <YAxis />
            <Tooltip />
            <Legend />
            <Line type="monotone" dataKey="dominant_freq" stroke="#1976d2" name="Frequency (Hz)" dot={false} isAnimationActive={false} />
          </LineChart>
        </ResponsiveContainer>
      </div>

      {/* Existing Log List */}
      <div style={{ display: 'grid', gap: '10px' }}>
        {/* Re-reverse the data for the list view so newest is on top */}
        {[...telemetry].reverse().slice(0, 10).map((log) => (
          <div key={log.id} style={{ 
            padding: '15px', 
            backgroundColor: log.machine_status === 'FAULTY' ? '#ffebee' : '#e8f5e9',
            borderLeft: `5px solid ${log.machine_status === 'FAULTY' ? '#f44336' : '#4caf50'}`,
            borderRadius: '4px'
          }}>
              <strong>{log.machine_status}</strong> | X: {log.x_axis} | Y: {log.y_axis} | Z: {log.z_axis} | 
            Freq: {log.dominant_freq}Hz | Amp: {log.peak_amplitude?.toFixed(2)} | 
            Temp: {log.temperature}°C | Current: {log.current}A      
          </div>
        ))}
      </div>
    </div>
  );
}