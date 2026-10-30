from django.db import models

# Create your models here.
class VibrationLog(models.Model):
    timestamp = models.DateTimeField(auto_now_add=True)
    x_axis = models.FloatField()
    y_axis = models.FloatField()
    z_axis = models.FloatField()
    machine_status = models.CharField(max_length=20)  # 'HEALTHY' or 'FAULTY'
    
    dominant_freq = models.FloatField(null=True, blank=True)
    peak_amplitude = models.FloatField(null=True, blank=True)

    temperature = models.FloatField(null=True, blank=True)
    current = models.FloatField(null=True, blank=True)

    def __str__(self):
        return f"{self.timestamp.strftime('%Y-%m-%d %H:%M:%S')} - {self.machine_status}"